#include "ViewModel.h"
#include "../fs/FSHandler.h"
#include "../fs/FSException.h"

using namespace FileB;

ViewModel::ViewModel() :
		current_files(new (std::list<File*>)) {
	// TODO Auto-generated constructor stub

}

ViewModel::~ViewModel() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<const std::list<File*>> ViewModel::getCurrentFiles() const {
	return current_files;
}

void ViewModel::showPath(const Path& path) {
	std::shared_ptr<const Directory> dir;
	try {
		dir = FSHandler::instance().listDir(path);
	} catch(FSException&) {
		throw;
	}
	current_files = dir;
	current_path = path;
	notify();
}

const Path& FileB::ViewModel::getCurrentPath() const {
	return current_path;
}
