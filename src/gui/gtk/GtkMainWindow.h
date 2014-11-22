#ifndef GTKMAINWINDOW_H
#define GTKMAINWINDOW_H

#include <gtkmm.h>

#include "../MainWindow.h"
#include "GtkPane.h"
#include "GtkView.h"

namespace FileB {
	/// Main Window using the Gtk+ toolkit.
	class GtkMainWindow : public MainWindow, public Gtk::ApplicationWindow {
	public:
		GtkMainWindow(Controller& c);
		virtual ~GtkMainWindow();
		GtkPane& getActivePane();
		GtkView& getActiveView();
	private:
        Gtk::Grid grid;
		Gtk::Entry addr_bar;
		Glib::RefPtr<Gtk::EntryBuffer> addr_buf;
	};
}

#endif
