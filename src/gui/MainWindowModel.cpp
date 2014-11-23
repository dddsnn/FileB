#include "MainWindowModel.h"

using namespace FileB;

MainWindowModel::MainWindowModel() {
	// TODO Auto-generated constructor stub

}

MainWindowModel::~MainWindowModel() {
	// TODO Auto-generated destructor stub
}

void FileB::MainWindowModel::showPath(Path path) {
	current_path = path;
	notify();
}

const Path& FileB::MainWindowModel::getCurrentPath() const {
	return current_path;
}
