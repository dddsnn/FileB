#include "ViewModel.h"

using namespace FileB;

ViewModel::ViewModel() :
		current_files() {
	// TODO Auto-generated constructor stub

}

ViewModel::~ViewModel() {
	// TODO Auto-generated destructor stub
}

const std::list<const File*>& ViewModel::getCurrentFiles() const {
	return current_files;
}

void ViewModel::showDir(const Directory& dir) {
	current_files.clear();
	// TODO there's gotta be a better way than copying. manually.
	for(Directory::const_iterator i = dir.begin(); i != dir.end(); i++) {
		current_files.push_back(*i);
	}
	notify();
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
}
