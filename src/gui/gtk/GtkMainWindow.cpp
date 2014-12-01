#include "GtkMainWindow.h"
#include "GtkPane.h"
#include "../../Application.h"
#include "../../Controller.h"
#include "../../fs/FSHandler.h"

#include <iostream>

using namespace FileB;

GtkMainWindow::GtkMainWindow(Controller& c, Model& model) :
		MainWindow(c, model), btn_up("Up"), btn_back("Back"), btn_forward(
				"Forward") {
//	panes.push_back(new GtkPane(controller));
//	act_pane = panes[0];
	// make the widgets take up all available space
	addr_bar.set_hexpand();
//	for(std::vector<Pane*>::iterator i = panes.begin(); i != panes.end(); i++) {
//		dynamic_cast<GtkPane*>(*i)->set_vexpand();
//	}

	// signal handlers
	btn_back.signal_clicked().connect(
			sigc::mem_fun(&controller, &Controller::onBackBtnActivated));
	btn_forward.signal_clicked().connect(
			sigc::mem_fun(&controller, &Controller::onForwardBtnActivated));
	btn_up.signal_clicked().connect(
			sigc::mem_fun(&controller, &Controller::onUpBtnActivated));
	addr_bar.signal_activate().connect(
			sigc::mem_fun(this, &GtkMainWindow::onAddrBarActivated));

	// add and fill grid
	add(grid);
	grid.attach(btn_back, 0, 0, 1, 1);
	grid.attach(btn_forward, 1, 0, 1, 1);
	grid.attach(btn_up, 2, 0, 1, 1);
	grid.attach(addr_bar, 3, 0, 1, 1);
//	grid.attach(*(dynamic_cast<GtkPane*>(panes[0])), 0, 1, 2, 1);

//	Directory dir(Path("/home/dddsnn"));
//	controller.onFileActivated(&dir); //getActiveView().getModel().showDir(Path("/home/dddsnn"));

	show_all_children();
}

GtkMainWindow::~GtkMainWindow() {
}

void FileB::GtkMainWindow::update() {
	// set the address bar
	std::string path_string(model.getCurrentPath().getPathString());
	// append a trailing slash unless root
	if(path_string != "/")
		path_string += "/";
	addr_bar.get_buffer()->set_text(path_string);

	// activate back/forward buttons
	btn_back.set_sensitive(model.hasBackHistory());
	btn_forward.set_sensitive(model.hasForwardHistory());
}

void FileB::GtkMainWindow::onAddrBarActivated() const {
	Path path(addr_bar.get_buffer()->get_text().raw());
	controller.onPathActivated(path);
}

void FileB::GtkMainWindow::addPane(GtkPane* pane, int pane_id) {
	MainWindow::addPane(pane, pane_id);
	grid.attach(*pane, 0, 1, 4, 1);
	show_all_children();
}

void FileB::GtkMainWindow::addView(GtkView* view, int pane_id, int view_id) {
	GtkPane* pane;
	try {
		pane = dynamic_cast<GtkPane*>(panes[pane_id]);
	} catch(std::out_of_range&) {
		throw;
	}
	pane->addView(view, view_id);
	show_all_children();
}
