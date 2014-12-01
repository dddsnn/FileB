#include "Model.h"

using namespace FileB;

Model::Model() :
		active_view_id(-1), view_models() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void FileB::Model::showPath(const Path& path) {
	current_path = path;
	if(active_view_id != -1) {
		view_models[active_view_id]->showPath(path);
	}
	notify();
}

const Path& FileB::Model::getCurrentPath() const {
	return current_path;
}

void FileB::Model::addViewModel(int id, ViewModel* view_model) {
	view_models[id] = view_model;
	if(active_view_id == -1)
		active_view_id = id;
}
