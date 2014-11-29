#ifndef SRC_GUI_GTK_GTKMAINWINDOW_H_
#define SRC_GUI_GTK_GTKMAINWINDOW_H_

#include <gtkmm.h>

#include "../MainWindow.h"
#include "GtkPane.h"
#include "GtkView.h"

namespace FileB {
/// Main Window using the Gtk+ toolkit.
class GtkMainWindow: public MainWindow, public Gtk::ApplicationWindow {
	public:
		GtkMainWindow(Controller& c, Model& model);
		virtual ~GtkMainWindow();
		void update();
		void onAddrBarActivated() const;
		void addPane(GtkPane* pane, int pane_id);
		void addView(GtkView* view, int pane_id, int view_id);
	private:
		Gtk::Grid grid;
		Gtk::Entry addr_bar;
		Gtk::Button btn_up;
};
}

#endif
