#include "Model.h"

using namespace FileB;

Model::Model() :
		view_models() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void FileB::Model::showPath(const Path& path) {
	current_path = path;
	notify();
}

const Path& FileB::Model::getCurrentPath() const {
	return current_path;
}

void FileB::Model::addViewModel(int id, ViewModel* view_model) {
	view_models[id] = view_model;
}
