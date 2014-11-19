#include "ViewModel.h"

using namespace FileB;

ViewModel::ViewModel() : current_dir() {
	// TODO Auto-generated constructor stub

}

ViewModel::~ViewModel() {
	// TODO Auto-generated destructor stub
}

const Directory* ViewModel::getCurrentDir() const {
	return current_dir;
}
//void GtkView::showDir(Path path) {
//	Directory const* dir = FSHandler::instance().listDir(path);
//	tree_model->clear();
//	Gtk::TreeModel::Row row;
//	for(std::vector<File*>::const_iterator i = dir->begin(); i != dir->end();
//			i++) {
//		// don't show . or ..
//		if((*i)->isDot())
//			continue;
//		// TODO settings replacement
//		bool show_hidden = false;
//		if(!show_hidden && (*i)->isHidden())
//			continue;
//		row = *(tree_model->append());
//		row[cols.name] = *i;
//	}
//	// TODO
//	// vsettings.current_dir = dir;
//}
