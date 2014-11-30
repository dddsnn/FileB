#ifndef SRC_GUI_PANE_H_
#define SRC_GUI_PANE_H_

#include <map>

#include "../globals.h"
#include "../Controller.h"
#include "View.h"

namespace FileB {
/// Abstract class for a pane.
/**
 * Panes contain multiple \link View Views\endlink.
 * They can be split horizontally or vertically.
 * This class should be subclassed implementing an actual pane with
 * a specific toolkit.
 */
class Pane {
	public:
		virtual ~Pane();
		virtual void addView(View* view, int view_id);
		static int newPaneGUID();
		int getId() const;

	protected:
		Pane(Controller& c, int id);
		Controller& controller;
		std::map<int, View*> views;
		int id;

	private:
		static int last_id;
};
}

#endif
