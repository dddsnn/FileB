#include "GtkMainWindow.h"
#include "GtkPane.h"
#include "../../Application.h"
#include "../../Controller.h"
#include "../../fs/FSHandler.h"

#include <iostream>

using namespace FileB;

GtkMainWindow::GtkMainWindow(Controller& c) :
		MainWindow(c) {
	panes.push_back(new GtkPane(controller));
	act_pane = panes[0];
	addr_buf = Gtk::EntryBuffer::create();
	// make the widgets take up all available space
	addr_bar.set_hexpand();
	for(std::vector<Pane*>::iterator i = panes.begin(); i != panes.end(); i++) {
		dynamic_cast<GtkPane*>(*i)->set_vexpand();
	}
	// add and fill grid
	add(grid);
	grid.attach(addr_bar, 0, 0, 1, 1);
	grid.attach(*(dynamic_cast<GtkPane*>(panes[0])), 0, 1, 1, 1);

	// TODO
	Directory const* dir = FSHandler::instance().listDir(Path("/home/dddsnn"));
//	std::list<const File*> files;
//	for(Directory::const_iterator i = dir->begin(); i!=dir->end(); i++){
//		files.push_back(*i);
//	}
	getActiveView().getModel().showDir(*dir);

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

void GtkMainWindow::showDir(Path p) {
	addr_bar.get_buffer()->set_text(p.getPathString());
	//TODO getActiveView().showDir(p);
}
