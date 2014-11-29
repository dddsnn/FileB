#include "Pane.h"

using namespace FileB;

int Pane::last_id = 0;

Pane::Pane(Controller& c, int id) :
		//TODO active id -1 is ugly
		controller(c), id(id), active_view_id(-1) {
}

Pane::~Pane() {
	for(std::map<int, View*>::iterator i = views.begin(); i != views.end(); i++)
		delete i->second;
}

void FileB::Pane::addView(View* view, int view_id) {
	views[id] = view;
	if(active_view_id == -1)
		active_view_id = id;
}

int FileB::Pane::newPaneGUID() {
	int id = Pane::last_id;
	Pane::last_id++;
	return id;
}

int FileB::Pane::getId() const {
	return id;
}
