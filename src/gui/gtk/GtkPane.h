#ifndef GTKPANE_H
#define GTKPANE_H

#include <gtkmm.h>

#include "../Pane.h"
#include "GtkView.h"

namespace FileB {
	/// Pane using the Gtk+ toolkit.
	class GtkPane : public Pane, public Gtk::Alignment {
	public:
		GtkPane(const struct Settings& s);
		virtual ~GtkPane();
		GtkView& getActiveView();
	private:
	};
}

#endif
