#include "View.h"

using namespace FileB;

View::View(Controller& c) :
		controller(c), model() {
//		Observer(dynamic_cast<Observable*>(&model)), controller(c) {
//	vsettings.current_dir;
	observe(dynamic_cast<Observable*>(&model));
}

View::~View() {
}

ViewModel& FileB::View::getModel() {
	return model;
}
