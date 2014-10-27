#include <stdexcept>
#include <iostream>

#include "Path.h"
#include "Directory.h"

using namespace FileB;

Path::Path() :
	path("/") {}

Path::Path(const std::string p) :
	path(p)
{
	// all paths must start with '/'
	if(path.empty() || path[0] != '/')
		throw std::invalid_argument("Paths must start with '/'");
	// every file must have a name (no "//" substring)
	if(path.find("//") != std::string::npos)
		throw std::invalid_argument("Paths cannot contain \"//\"");
	// erase trailing slash
	if(path[path.size() - 1] == '/' && path.size() > 1)
		path.erase(path.size() - 1);
}

Path::Path(const Directory dir, std::string name) {
	if(name[name.size() - 1] == '/' && path.size() > 1)
		name.erase(name.size() - 1);
	// make sure the name isn't a path
	if(name.find('/') != std::string::npos)
		throw std::invalid_argument("The name cannot be a path");
	path = dir.getPath().path;
	// don't append a slash to root
	if(path.size() > 1)
		path.append("/");
	path.append(name);
}

Path::~Path() {}

std::string Path::getBaseName() const {
	if(!path.compare("/"))
		return path;
	return path.substr(path.find_last_of('/') + 1);
}

void Path::append(std::string name) {
	// erase trailing slash
	if(name[name.size() - 1] == '/' && path.size() > 1)
		name.erase(name.size() - 1);
	// make sure the name isn't a path
	if(name.find('/') != std::string::npos)
		throw std::invalid_argument("The name cannot be a path");
	// don't append a slash to root
	if(path.size() > 1)
		path.append("/");
	path.append(name);
}

std::string Path::getPathString() const {
	return path;
}

/**
 * Root ("/") has depth 0, a directory in root ("/etc") has depth 1 etc.
 */
unsigned int Path::getDepth() const {
	if(!path.empty() && path.size() == 1)
		return 0;
	unsigned int count = 0;
	for(unsigned int i = 0; i < path.size() ; i++)
		if(path[i] == '/')
			count++;
	return count;
}

/**
 * \returns a truncated path that has depth level.
 * 	The same path if level exceeds the depth.
 */
Path Path::getLevel(unsigned int level) const {
	if(getDepth() < level)
		return Path(*this);
	// root
	if(level == 0)
		return Path("/");
	Path np(*this);
//	std::cout << "a" << np.path << "b" << std::endl;
	while(np.getDepth() > level){
//		std::cout << np.path << std::endl;
		np.path = np.path.substr(0, np.path.find_last_of('/'));
//		std::cout << np.path << std::endl;
	}
//	std::cout << np.getDepth() << level << std::endl;
	return np;
}
