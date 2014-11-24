#ifndef SRC_GUI_GTK_GTKMAINWINDOW_H_
#define SRC_GUI_GTK_GTKMAINWINDOW_H_

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
		void update();
	private:
        Gtk::Grid grid;
		Gtk::Entry addr_bar;
		Gtk::Button btn_up;
		Glib::RefPtr<Gtk::EntryBuffer> addr_buf;
	};
}

#endif
