#include "../../Application.h"
#include "GtkPane.h"
#include "GtkView.h"
#include "../../Controller.h"

using namespace FileB;

GtkPane::GtkPane(const Controller& c) :
		Pane(c) {
	views.push_back(new GtkView(controller));
	act_view = views[0];
	add(*(dynamic_cast<GtkView*>(views[0])));
}

GtkPane::~GtkPane() {
	for(std::vector<View*>::iterator i = views.begin(); i != views.end(); i++)
		delete *i;
}

GtkView& GtkPane::getActiveView() {
	return *dynamic_cast<GtkView*>(act_view);
}
