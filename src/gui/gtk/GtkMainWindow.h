#ifndef GTKMAINWINDOW_H
#define GTKMAINWINDOW_H

#include <gtkmm.h>

#include "../../Application.h"
#include "../MainWindow.h"
#include "GtkPane.h"
#include "GtkView.h"

namespace FileB {
	/// Main Window using the Gtk+ toolkit.
	class GtkMainWindow : public MainWindow, public Gtk::Window {
	public:
		GtkMainWindow(const struct Settings& s);
		virtual ~GtkMainWindow();
		GtkPane& getActivePane();
		GtkView& getActiveView();
		void showDir(Path p);
	private:
        Gtk::Grid grid;
		Gtk::Entry addr_bar;
		Glib::RefPtr<Gtk::EntryBuffer> addr_buf;
	};
}

#endif
