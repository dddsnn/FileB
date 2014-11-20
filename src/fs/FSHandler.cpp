#include "FSHandler.h"
#include "../Application.h"

#include <dirent.h>
#include <iostream>
#include <errno.h>
#include <cstdlib>
#include <stdexcept>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sstream>

using namespace FileB;

FSHandler::FSHandler() :
	root(new Directory()) {}

FSHandler::~FSHandler() {}

FSHandler* FSHandler::m_instance = 0;
FSHandler& FSHandler::instance() {
	if(!m_instance)
		m_instance = new FSHandler();
	return *m_instance;
}

/**
 * The listed files are not ordered.
 */
Directory const* FSHandler::listDir(const Path path) {
	Directory* dir = getDir(path);
	if(dir->isComplete())
		return dir;
	DIR* dp;
	struct dirent64* ep;
	dp = safeOpenDir(path);
	while((ep = readdir64(dp))) {
		Path np(path);
		np.append(std::string(ep->d_name));
		File* f;
		/* set the type of the file if supported
		 * this funcionality is provided by stat, just distinguish
		 * between files and directories
		 */
		#ifdef _DIRENT_HAVE_D_TYPE
		if(ep->d_type == DT_DIR)
			f = new Directory(np);
		else
			f = new File(np);
/*		switch(ep->d_type) {
		case DT_UNKNOWN:
			f = new File(np, File::TYPE_UNKNOWN);
			break;
		case DT_REG:
			f = new File(np, File::TYPE_REGULAR);
			break;
		case DT_DIR:
			f = new Directory(np);
			break;
		case DT_FIFO:
			f = new File(np, File::TYPE_FIFO);
			break;
		case DT_SOCK:
			f = new File(np, File::TYPE_SOCKET);
			break;
		case DT_CHR:
			f = new File(np, File::TYPE_CHAR);
			break;
		case DT_BLK:
			f = new File(np, File::TYPE_BLOCK);
			break;
		} */
		#else
		f = new File(np);
		#endif
		safeStat(f);
		dir->push_back(f);
	}
	safeCloseDir(dp);
	dir->markComplete();
	return dir;
}

Directory* FSHandler::getDir(const Path path) {
	if(path.getDepth() == 0)
		return root;
	Directory* parent = getDir(path.getLevel(path.getDepth() - 1));
	// check if parent already contains the file
	for(std::list<File*>::iterator i = parent->begin();
		i != parent->end(); i++)
		{
		if(!(*i)->getName().compare(path.getBaseName()))
			return dynamic_cast<Directory*>(*i);
	}
	// check if the requested directory exists
	DIR* dir = opendir(path.getPathString().c_str());
	if(!dir)
		throw std::invalid_argument(path.getPathString());
	
	Directory* child = new Directory(*parent, path.getBaseName());
	parent->push_back(child);
	return child;
}

/**
 * \returns the dirstream of the directory specified by path.
 * 	Exits on failure (never returns 0).
 */
DIR* FSHandler::safeOpenDir(const Path path) {
	DIR* dir = opendir(path.getPathString().c_str());
	if(!dir){
		switch(errno) {
		case ENAMETOOLONG:
			std::cerr << "A name in " <<
				path.getPathString()
				<< " was too long." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENOENT:
			std::cerr << path.getPathString() <<
				" does not exist." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENOTDIR:
			std::cerr << path.getPathString() <<
				" is not a directory." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ELOOP:
			std::cerr << "Too many symbolic links were resolved "
				"while trying to look up " <<
				path.getPathString() << std::endl;
			exit(EXIT_FAILURE);
			break;
		case EACCES:
			std::cerr << "Read permission denied for " <<
				path.getPathString()
				<< ", terminating." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case EMFILE:
			std::cerr << "Process has too many files open,"
				" terminating." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENFILE:
			std::cerr << "The system cannot open any more files,"
				" terminating." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENOMEM:
			std::cerr << "Out of memory, terminating." << std::endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
	return dir;
}

void FSHandler::safeCloseDir(DIR* dir) {
	if(closedir(dir)) {
		std::cerr << "Failed to close a directory stream" <<
			", terminating." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void FSHandler::safeStat(File* f) {
	struct stat64 s;
	if(!stat64(f->getPath().getPathString().c_str(), &s)) {
		switch(errno){
		case ENAMETOOLONG:
			std::cerr << "A name in " <<
				f->getPath().getPathString()
				<< " was too long." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENOENT:
			std::cerr << f->getPath().getPathString() <<
				" does not exist." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ENOTDIR:
			std::cerr << "A directory component in " <<
				f->getPath().getPathString() <<
				" is not a directory." << std::endl;
			exit(EXIT_FAILURE);
			break;
		case ELOOP:
			std::cerr << "Too many symbolic links were resolved "
				"while trying to look up " <<
				f->getPath().getPathString() << std::endl;
			exit(EXIT_FAILURE);
			break;
		case EACCES:
			std::cerr << "Read permission denied for " <<
				f->getPath().getPathString()
				<< ", terminating." << std::endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
	// set type
	if(S_ISREG(s.st_mode))
		f->setType(File::TYPE_REGULAR);
	else if(S_ISDIR(s.st_mode))
		f->setType(File::TYPE_DIRECTORY);
	else if(S_ISLNK(s.st_mode))
		f->setType(File::TYPE_LINK);
	else if(S_ISFIFO(s.st_mode))
		f->setType(File::TYPE_FIFO);
	else if(S_ISCHR(s.st_mode))
		f->setType(File::TYPE_CHAR);
	else if(S_ISBLK(s.st_mode))
		f->setType(File::TYPE_BLOCK);
	else if(S_ISSOCK(s.st_mode))
		f->setType(File::TYPE_SOCKET);
	else if(S_TYPEISMQ(&s))
		f->setType(File::TYPE_MSGQ);
	else if(S_TYPEISSEM(&s))
		f->setType(File::TYPE_SEM);
	else if(S_TYPEISSEM(&s))
		f->setType(File::TYPE_SHMEM);
	f->setOwner(s.st_uid);
	f->setGroup(s.st_gid);
	f->setSize(s.st_size);
	f->setMTime(s.st_mtime);
}

/**
 * \returns the user name matching uid or the uid as a string if no user name
 * 	exists for that uid.
 */
std::string FSHandler::getUserName(uid_t uid) const {
	struct passwd* pw = getpwuid(uid);
	if(pw)
		return std::string(pw->pw_name);
	else {
		std::ostringstream s;
		s << uid;
		return s.str();
	}
}

/**
 * \returns the group name matching gid or the gid as a string if no group name
 * 	exists for that gid.
 */
std::string FSHandler::getGroupName(gid_t gid) const {
	struct group* g = getgrgid(gid);
	if(g)
		return std::string(g->gr_name);
	else {
		std::ostringstream s;
		s << gid;
		return s.str();
	}
}
