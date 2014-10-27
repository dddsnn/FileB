#include "GtkPane.h"
#include "GtkView.h"

using namespace FileB;

GtkPane::GtkPane(const struct Settings& s):
	Pane(s)
{
	views.push_back(new GtkView(settings));
	act_view = views[0];
	add(*(dynamic_cast<GtkView*>(views[0])));
}

GtkPane::~GtkPane() {
	for(std::vector<View*>::iterator i = views.begin();
		i != views.end(); i++)
		delete *i;
}

GtkView& GtkPane::getActiveView() {
	return *dynamic_cast<GtkView*>(act_view);
}
