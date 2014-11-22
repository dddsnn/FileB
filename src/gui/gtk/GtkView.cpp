#include "GtkView.h"
#include "../../fs/FSHandler.h"
#include "../../Application.h"

#include <iostream>
#include <string>

using namespace FileB;

GtkView::GtkView(Controller& c) :
		View(c), cols(), tree_model(Gtk::TreeStore::create(cols)), tree(
				new Gtk::TreeView(tree_model)) {
	tree->signal_row_activated().connect(
			sigc::mem_fun(this, &GtkView::onRowActivated));

	// add the columns
	viewcol_name.set_title("Name");
	viewcol_name.pack_start(cellrend_name);
	viewcol_name.set_reorderable();
	tree->append_column(viewcol_name);
	viewcol_name.set_cell_data_func(cellrend_name,
			sigc::mem_fun(this, &GtkView::updateNameCol));

	viewcol_content.set_title("Type");
	viewcol_content.pack_start(cellrend_content);
	viewcol_content.set_reorderable();
	tree->append_column(viewcol_content);
	viewcol_content.set_cell_data_func(cellrend_content,
			sigc::mem_fun(this, &GtkView::updateContentCol));

	viewcol_size.set_title("Size");
	viewcol_size.pack_start(cellrend_size);
	viewcol_size.set_reorderable();
	tree->append_column(viewcol_size);
	viewcol_size.set_cell_data_func(cellrend_size,
			sigc::mem_fun(this, &GtkView::updateSizeCol));

	viewcol_owner.set_title("Owner");
	viewcol_owner.pack_start(cellrend_owner);
	viewcol_owner.set_reorderable();
	tree->append_column(viewcol_owner);
	viewcol_owner.set_cell_data_func(cellrend_owner,
			sigc::mem_fun(this, &GtkView::updateOwnerCol));

	viewcol_group.set_title("Group");
	viewcol_group.pack_start(cellrend_group);
	viewcol_group.set_reorderable();
	tree->append_column(viewcol_group);
	viewcol_group.set_cell_data_func(cellrend_group,
			sigc::mem_fun(this, &GtkView::updateGroupCol));

	viewcol_mtime.set_title("Last modified");
	viewcol_mtime.pack_start(cellrend_mtime);
	viewcol_mtime.set_reorderable();
	tree->append_column(viewcol_mtime);
	viewcol_mtime.set_cell_data_func(cellrend_mtime,
			sigc::mem_fun(this, &GtkView::updateMTimeCol));

	add(*tree);
}

GtkView::~GtkView() {
}

void GtkView::showFiles(const std::list<File*>& files) {
	tree_model->clear();
	Gtk::TreeModel::Row row;
	std::list<File*>::const_iterator j = files.begin();
	for(std::list<File*>::const_iterator i = files.begin(); i != files.end();
			i++) {
		// don't show . or ..
		if((*i)->isDot())
			continue;
		// TODO settings replacement
		bool show_hidden = false;
		if(!show_hidden && (*i)->isHidden())
			continue;
		row = *(tree_model->append());
		row.set_value(cols.name, (*i)->getName());
//		row[cols.name] = (*i)->getName();
		row[cols.content] = (*i)->getContent();
		row[cols.size] = (*i)->getSize();
		row[cols.owner] = (*i)->getOwner();
		row[cols.group] = (*i)->getGroup();
		row[cols.mtime] = (*i)->getMTime();
		row[cols.file] = *i;
	}
	// TODO
	// vsettings.current_dir = dir;
}

void GtkView::onRowActivated(const Gtk::TreeModel::Path& p,
		Gtk::TreeViewColumn*) {
	Gtk::TreeModel::Row row = *(tree_model->get_iter(p));
	controller.onFileActivated(row[cols.file]);
}

void GtkView::updateNameCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		std::string name = i->get_value(cols.name);
//		std::cout << i->get_value(cols.file)->getName() << std::endl;
		Glib::ustring text = Glib::locale_from_utf8(name);
		cellrend_name.property_text() = text;
	}
}

void GtkView::updateContentCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		int content = i->get_value(cols.content);
		Glib::ustring text;
		switch(content) {
		case File::CONTENT_UNKNOWN:
			text = "unknown";
			break;
		case File::CONTENT_DIRECTORY:
			text = "directory";
			break;
		default:
			text = "";
		}
		cellrend_content.property_text() = text;
	}
}

void GtkView::updateSizeCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		File* f = i->get_value(cols.file);
		off_t size = f->getSize();
		// if it's a directory, don't display the size
		if(dynamic_cast<Directory*>(f)) {
			cellrend_size.property_text() = "";
		} else {
			// TODO settings replacement
			int prefix = Application::PREFIX_BASE_2;
			Glib::ustring text = Glib::locale_to_utf8(
					Application::getHumanReadableSize(size, prefix));
			cellrend_size.property_text() = text;
		}
	}
}

void GtkView::updateOwnerCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		uid_t owner = i->get_value(cols.owner);
		Glib::ustring text = Glib::locale_to_utf8(
				FSHandler::instance().getUserName(owner));
		cellrend_owner.property_text() = text;
	}
}

void GtkView::updateGroupCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		gid_t group = i->get_value(cols.group);
		Glib::ustring text = Glib::locale_to_utf8(
				FSHandler::instance().getGroupName(group));
		cellrend_group.property_text() = text;
	}
}

void GtkView::updateMTimeCol(Gtk::CellRenderer*,
		const Gtk::TreeModel::iterator& i) {
	if(i) {
		off_t mtime = i->get_value(cols.mtime);
		Glib::ustring text = Glib::locale_to_utf8(
				Application::getHumanReadableTime(mtime));
		cellrend_mtime.property_text() = text;
	}
}

void GtkView::update() {
	showFiles(*model.getCurrentFiles());
}
