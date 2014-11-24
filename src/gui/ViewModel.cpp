#include "ViewModel.h"
#include "../fs/FSHandler.h"

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

void ViewModel::showDir(const Path& path) {
	std::shared_ptr<const Directory> dir = FSHandler::instance().listDir(path);
	current_files = dir;
	notify();
}
