#include <stdexcept>
#include <iostream>

#include "File.h"
#include "Directory.h"

using namespace FileB;

File::File() :
	path("/"),
	content() {}

File::File(const Path p, int t) :
	path(p),
	type(t),
	content() {}

/**
 * \param dir the Directory this File resides in
 * \param name the name of this File, encoded in the system's locale
 * \param t the type of this file
 */
File::File(const Directory dir, std::string name, int t) :
	type(t),
	content()
{
	path = dir.getPath();
	path.append(name);
}

File::~File() {}

const std::string File::getName() const {
	return path.getBaseName();
}

const Path File::getPath() const {
	return path;
}

bool File::isDot() const {
	if(!getName().compare("..") || !getName().compare("."))
		return true;
	return false;
}

bool File::isHidden() const {
	if(getName()[0] == '.')
		return true;
	return false;
}

int File::getType() const {
	return type;
}

void File::setType(int t) {
	type = t;
}

const std::string& File::getContent() const {
	return content;
}

void File::setContent(const std::string& c) {
	content = c;
}

uid_t File::getOwner() const {
	return owner;
}

void File::setOwner(uid_t o) {
	owner = o;
}

gid_t File::getGroup() const {
	return group;
}

void File::setGroup(gid_t g) {
	group = g;
}

off_t File::getSize() const {
	return size;
}

void File::setSize(off_t s) {
	size = s;
}

time_t File::getMTime() const {
	return mtime;
}

void File::setMTime(time_t t) {
	mtime = t;
}
