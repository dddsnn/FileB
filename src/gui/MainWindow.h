#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <map>

#include "../Controller.h"
#include "../globals.h"
#include "Model.h"
#include "Pane.h"

namespace FileB {
/// Abstract class for the main window.
/**
 * The main window contains multiple \link Pane Panes\endlink.
 * This class should be subclassed implementing an actual window with
 * a specific toolkit.
 */
class MainWindow: public Observer {
	public:
		virtual ~MainWindow();
		virtual void update() = 0;
		virtual void addPane(Pane* pane, int pane_id);
		virtual void addView(View* view, int pane_id, int view_id);

	protected:
		MainWindow(Controller& c, Model& model);
		Controller& controller;
		std::map<int, Pane*> panes;
		Model& model;
};
}

#endif
