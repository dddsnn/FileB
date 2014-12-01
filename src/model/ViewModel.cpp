#include "ViewModel.h"
#include "../fs/FSHandler.h"
#include "../fs/FSException.h"

using namespace FileB;

ViewModel::ViewModel() :
		current_files(new (std::list<File*>)), history(History(Path("/"))) {
	// TODO Auto-generated constructor stub

}

ViewModel::~ViewModel() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<const std::list<File*>> ViewModel::getCurrentFiles() const {
	return current_files;
}

void ViewModel::activatePath(const Path& path) {
	history.addEntry(path);
	showPath(path);
}

const Path& FileB::ViewModel::showPreviousPath() {
	const Path& prev = history.goBack();
	showPath(prev);
	return prev;
}

const Path& FileB::ViewModel::showNextPath() {
	const Path& next = history.goForward();
	showPath(next);
	return next;
}

const Path& FileB::ViewModel::getCurrentPath() const {
	return history.getCurrentPath();
}

bool FileB::ViewModel::hasBackHistory() {
	return history.getBackDepth();
}

bool FileB::ViewModel::hasForwardHistory() {
	return history.getForwardDepth();
}

void FileB::ViewModel::showPath(const Path& path) {
	std::shared_ptr<const Directory> dir;
	dir = FSHandler::instance().listDir(path);
	current_files = dir;
	notify();
}
