#ifndef PANE_H
#define PANE_H

#include <vector>

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
		/// Returns the currently active View of this Pane.
		virtual View& getActiveView() = 0;
	protected:
		Pane(Controller& c);
		Controller& controller;
		std::vector<View*> views;
		View* act_view;
	};
}

#endif
