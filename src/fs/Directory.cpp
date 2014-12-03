#include "Directory.h"

using namespace FileB;

Directory::Directory() :
		File(), complete(false) {
	content = "directory";
}

Directory::Directory(const Path& path) :
		File(path, File::TYPE_DIRECTORY), complete(false) {
	content = "directory";
}

Directory::Directory(const Directory& dir, std::string name) :
		File(dir, name, File::TYPE_DIRECTORY), complete(false) {
	content = "directory";
}

Directory::~Directory() {
}

bool Directory::isComplete() const {
	return complete;
}

void Directory::markComplete() {
	complete = true;
}
