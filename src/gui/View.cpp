#include "View.h"

using namespace FileB;

View::View(Controller& c) :
		Observer(dynamic_cast<Observable*>(&model)), controller(c) {
//	vsettings.current_dir;
}

View::~View() {
}

ViewModel& FileB::View::getModel() {
	return model;
}
