#include "MainWindow.h"

using namespace FileB;

MainWindow::MainWindow(Controller& c) :
		controller(c), panes(), act_pane(0), model() {
	observe(dynamic_cast<Observable*>(&model));
}

MainWindow::~MainWindow() {
}

MainWindowModel& FileB::MainWindow::getModel() {
	return model;
}
