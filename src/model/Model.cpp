#include "Model.h"

using namespace FileB;

Model::Model() :
		active_view_id(-1), view_models() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void FileB::Model::activatePath(const Path& path) {
	if(active_view_id != -1) {
		view_models[active_view_id]->activatePath(path);
	}
	showPath(path);
}

const Path& FileB::Model::getCurrentPath() const {
	return current_path;
}

void FileB::Model::showPreviousPath() {
	ViewModel* view_model = 0;
	try {
		view_model = view_models[active_view_id];
	} catch(std::out_of_range& e) {
		//TODO check that view_model exists
	}
	const Path& prev = view_model->showPreviousPath();
	showPath(prev);
}

void FileB::Model::showNextPath() {
	ViewModel* view_model = 0;
	try {
		view_model = view_models[active_view_id];
	} catch(std::out_of_range& e) {
		//TODO check that view_model exists
	}
	const Path& next = view_model->showNextPath();
	showPath(next);
}

void FileB::Model::addViewModel(int id, ViewModel* view_model) {
	view_models[id] = view_model;
	if(active_view_id == -1)
		active_view_id = id;
}

bool FileB::Model::hasBackHistory() {
	ViewModel* view_model = 0;
	try {
		view_model = view_models[active_view_id];
	} catch(std::out_of_range& e) {
		//TODO check that view_model exists
	}
	return view_model->hasBackHistory();
}

bool FileB::Model::hasForwardHistory() {
	ViewModel* view_model = 0;
	try {
		view_model = view_models[active_view_id];
	} catch(std::out_of_range& e) {
		//TODO check that view_model exists
	}
	return view_model->hasForwardHistory();
}

void FileB::Model::showPath(const Path& path) {
	current_path = path;
	notify();
}
