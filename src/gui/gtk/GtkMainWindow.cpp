#include "GtkMainWindow.h"
#include "GtkPane.h"
#include "../../Application.h"
#include "../../Controller.h"
#include "../../fs/FSHandler.h"

#include <iostream>

using namespace FileB;

GtkMainWindow::GtkMainWindow(Controller& c) :
		MainWindow(c), btn_up(Glib::ustring("Up")) {
	panes.push_back(new GtkPane(controller));
	act_pane = panes[0];
	// make the widgets take up all available space
	addr_bar.set_hexpand();
	for(std::vector<Pane*>::iterator i = panes.begin(); i != panes.end(); i++) {
		dynamic_cast<GtkPane*>(*i)->set_vexpand();
	}

	// signal handlers
	btn_up.signal_clicked().connect(
			sigc::mem_fun(&controller, &Controller::onUpBtnActivated));
	addr_bar.signal_activate().connect(
			sigc::mem_fun(this, &GtkMainWindow::onAddrBarActivated));

	// add and fill grid
	add(grid);
	grid.attach(addr_bar, 1, 0, 1, 1);
	grid.attach(*(dynamic_cast<GtkPane*>(panes[0])), 0, 1, 2, 1);
	grid.attach(btn_up, 0, 0, 1, 1);

	Directory dir(Path("/home/dddsnn"));
	controller.onFileActivated(&dir); //getActiveView().getModel().showDir(Path("/home/dddsnn"));

	show_all_children();
}

GtkMainWindow::~GtkMainWindow() {
	for(std::vector<Pane*>::iterator i = panes.begin(); i != panes.end(); i++)
		delete *i;
}

GtkPane& GtkMainWindow::getActivePane() {
	return *dynamic_cast<GtkPane*>(act_pane);
}

GtkView& GtkMainWindow::getActiveView() {
	return getActivePane().getActiveView();
}

void FileB::GtkMainWindow::update() {
	std::string path_string(model.getCurrentPath().getPathString() + "/");
	addr_bar.get_buffer()->set_text(path_string);
}

void FileB::GtkMainWindow::onAddrBarActivated() const {
	Path path(addr_bar.get_buffer()->get_text().raw());
	controller.onPathActivated(path);
}
