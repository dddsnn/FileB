#include "FSHandler.h"
#include "../Application.h"
#include "FSException.h"

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

FSHandler::FSHandler() {
}

FSHandler::~FSHandler() {
}

FSHandler* FSHandler::m_instance = 0;
FSHandler& FSHandler::instance() {
	if(!m_instance)
		m_instance = new FSHandler();
	return *m_instance;
}

// TODO memory leaks cause directory contents aren't deleted (also make
// shared_ptr)

/**
 * The listed files are not ordered.
 */
std::shared_ptr<const Directory> FSHandler::listDir(const Path& path) {
	std::shared_ptr<Directory> dir = std::shared_ptr<Directory>(
			new Directory(path));
	DIR* dp;
	struct dirent64* ep;
	try {
		dp = safeOpenDir(path);
	} catch(FSException&) {
		throw;
	}
	while((ep = readdir64(dp))) {
		Path file_path(path);
		file_path.append(std::string(ep->d_name));

		// TODO since i use stat anyway, let it decide whether it's a file or
		// directory
//		File* f;
//		/* set the type of the file if supported
//		 * this funcionality is provided by stat, just distinguish
//		 * between files and directories
//		 */
//#ifdef _DIRENT_HAVE_D_TYPE
//		if(ep->d_type == DT_DIR)
//			f = new Directory(file_path);
//		else
//			f = new File(file_path);
//		/*		switch(ep->d_type) {
//		 case DT_UNKNOWN:
//		 f = new File(np, File::TYPE_UNKNOWN);
//		 break;
//		 case DT_REG:
//		 f = new File(np, File::TYPE_REGULAR);
//		 break;
//		 case DT_DIR:
//		 f = new Directory(np);
//		 break;
//		 case DT_FIFO:
//		 f = new File(np, File::TYPE_FIFO);
//		 break;
//		 case DT_SOCK:
//		 f = new File(np, File::TYPE_SOCKET);
//		 break;
//		 case DT_CHR:
//		 f = new File(np, File::TYPE_CHAR);
//		 break;
//		 case DT_BLK:
//		 f = new File(np, File::TYPE_BLOCK);
//		 break;
//		 } */
//#else
//		f = new File(file_path);
//#endif

		File* f;
		try {
			f = statFile(file_path);
		} catch(FSException&) {
			throw;
		}
		dir->push_back(f);
	}
	try {
		safeCloseDir(dp);
	} catch(FSException&) {
		throw;
	}
	dir->markComplete();
	return dir;
}

/**
 * \returns the dirstream of the directory specified by path.
 * 	Exits on failure (never returns 0).
 */
DIR* FSHandler::safeOpenDir(const Path path) {
	DIR* dir = opendir(path.getPathString().c_str());
	if(!dir) {
		switch(errno) {
		case ENAMETOOLONG:
			throw FSException(
					"A name in " + path.getPathString() + " was too long.");
			break;
		case ENOENT:
			throw FSException(path.getPathString() + " does not exist.");
			break;
		case ENOTDIR:
			throw FSException(path.getPathString() + " is not a directory.");
			break;
		case ELOOP:
			throw FSException("Too many symbolic links were resolved "
					"while trying to look up " + path.getPathString());
			break;
		case EACCES:
			throw FSException(
					"Read permission denied for " + path.getPathString());
			break;
		case EMFILE:
			throw FSException("Process has too many files open");
			break;
		case ENFILE:
			throw FSException("The system cannot open any more files");
			break;
		case ENOMEM:
			throw FSException("Out of memory");
			break;
		}
	}
	return dir;
}

void FSHandler::safeCloseDir(DIR* dir) {
	if(closedir(dir)) {
		throw FSException("Failed to close a directory stream.");
	}
}

File* FSHandler::statFile(const Path& path) {
	struct stat64 s;
	File* f;
	if(!stat64(path.getPathString().c_str(), &s)) {
		switch(errno) {
		case ENAMETOOLONG:
			throw FSException(
					"A name in " + path.getPathString() + " was too long.");
			break;
		case ENOENT:
			throw FSException(path.getPathString() + " does not exist.");
			break;
		case ENOTDIR:
			throw FSException(
					"A directory component in " + path.getPathString()
							+ " is not a directory.");
			break;
		case ELOOP:
			throw FSException("Too many symbolic links were resolved "
					"while trying to look up " + path.getPathString());
			break;
		case EACCES:
			throw FSException(
					"Read permission denied for " + path.getPathString());
			break;
		}
	}
	// create File or Directory, depending on type
	if(S_ISDIR(s.st_mode))
		f = new Directory(path);
	else {
		f = new File(path);
		// set type
		if(S_ISREG(s.st_mode))
			f->setType(File::TYPE_REGULAR);
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
	}
	f->setOwner(s.st_uid);
	f->setGroup(s.st_gid);
	f->setSize(s.st_size);
	f->setMTime(s.st_mtime);

	return f;
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
