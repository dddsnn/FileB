#include "View.h"

using namespace FileB;

int View::last_id = 0;

View::View(Controller& c, ViewModel& model, int id) :
		Observer(dynamic_cast<Observable*>(&model)), id(id), controller(c), model(
				model) {
//	vsettings.current_dir;
//	observe(dynamic_cast<Observable*>(&model));
}

View::~View() {
}

int FileB::View::newViewGUID() {
	int id = View::last_id;
	View::last_id++;
	return id;
}

int FileB::View::getId() const {
	return id;
}
