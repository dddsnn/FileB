#include "../../Application.h"
#include "GtkPane.h"
#include "GtkView.h"
#include "../../Controller.h"

using namespace FileB;

GtkPane::GtkPane(Controller& c, int id) :
		Pane(c, id) {
}

GtkPane::~GtkPane() {
}
void FileB::GtkPane::addView(GtkView* view, int id) {
	Pane::addView(view, id);
	add(*view);
}
