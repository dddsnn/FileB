#include "View.h"

using namespace FileB;

int View::last_id = 0;

View::View(Controller& c, ViewModel& model, int id) :
		controller(c), model(model), id(id) {
//		Observer(dynamic_cast<Observable*>(&model)), controller(c) {
//	vsettings.current_dir;
	observe(dynamic_cast<Observable*>(&model));
}

View::~View() {
}

ViewModel& FileB::View::getModel() {
	return model;
}

int FileB::View::newViewGUID() {
	int id = View::last_id;
	View::last_id++;
	return id;
}

int FileB::View::getId() const {
	return id;
}
