#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include "../Application.h"
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
		/// Shows a directory in the active View.
		virtual void showDir(Path p) = 0;
	protected:
		MainWindow(const struct Settings& s);
		const struct Settings settings;
		std::vector<Pane*> panes;
		Pane* act_pane;
	};
}

#endif
