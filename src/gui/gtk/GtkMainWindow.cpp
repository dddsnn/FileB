#include "GtkMainWindow.h"
#include "GtkPane.h"

using namespace FileB;

GtkMainWindow::GtkMainWindow(const struct Settings& s):
	MainWindow(s)
{
	panes.push_back(new GtkPane(settings));
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
	showDir(Path("/home/dddsnn"));
	show_all_children();
}

GtkMainWindow::~GtkMainWindow() {
	for(std::vector<Pane*>::iterator i = panes.begin();
		i != panes.end(); i++)
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
	getActiveView().showDir(p);
}
