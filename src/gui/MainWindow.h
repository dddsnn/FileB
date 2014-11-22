#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <vector>

#include "../Controller.h"
#include "../globals.h"
#include "Pane.h"

namespace FileB {
	/// Abstract class for the main window.
	/**
	 * The main window contains multiple \link Pane Panes\endlink.
	 * This class should be subclassed implementing an actual window with
	 * a specific toolkit.
	 */
	class MainWindow {
	public:
		virtual ~MainWindow();
		/// Returns the currently active Pane of this window.
		virtual Pane& getActivePane() = 0;
		/// Returns the currently active View of this window.
		virtual View& getActiveView() = 0;
	protected:
		MainWindow(Controller& c);
		Controller& controller;
		std::vector<Pane*> panes;
		Pane* act_pane;
	};
}

#endif
