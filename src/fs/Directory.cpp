#include "Directory.h"

using namespace FileB;

Directory::Directory() :
	File(),
	complete(false)
{
	content = File::CONTENT_DIRECTORY;
}

Directory::Directory(const Path& path) :
	File(path, File::TYPE_DIRECTORY),
	complete(false)
{
	content = File::CONTENT_DIRECTORY;
}

Directory::Directory(const Directory& dir, std::string name) :
	File(dir, name, File::TYPE_DIRECTORY),
	complete(false)
{
	content = File::CONTENT_DIRECTORY;
}

Directory::~Directory() {}

bool Directory::isComplete() const {
	return complete;
}

void Directory::markComplete() {
	complete = true;
}
