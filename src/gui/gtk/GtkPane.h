#ifndef SRC_GUI_GTK_GTKPANE_H_
#define SRC_GUI_GTK_GTKPANE_H_

#include <gtkmm.h>

#include "../Pane.h"
#include "GtkView.h"

namespace FileB {
/// Pane using the Gtk+ toolkit.
class GtkPane: public Pane, public Gtk::Alignment {
	public:
		GtkPane(Controller& c, int id);
		virtual ~GtkPane();
		void addView(GtkView* view, int id);
};
}

#endif
