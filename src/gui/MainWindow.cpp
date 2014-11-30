#include "MainWindow.h"

using namespace FileB;

MainWindow::MainWindow(Controller& c, Model& model) :
		Observer(dynamic_cast<Observable*>(&model)),
		//TODO active id -1 is ugly
		controller(c), panes(), model(model) {
//	observe(dynamic_cast<Observable*>(&model));
}

MainWindow::~MainWindow() {
	for(std::map<int, Pane*>::iterator i = panes.begin(); i != panes.end(); i++)
		delete i->second;
}

void FileB::MainWindow::addPane(Pane* pane, int pane_id) {
	panes[pane_id] = pane;
}

void FileB::MainWindow::addView(View* view, int pane_id, int view_id) {
	// TODO useless? because i need to call it from gtkmainwindow to get the
	// gtkpane anyway?
	Pane* pane;
	try {
		pane = panes[pane_id];
	} catch(std::out_of_range&) {
		throw;
	}
	pane->addView(view, view_id);
}
