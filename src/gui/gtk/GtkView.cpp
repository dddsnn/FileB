#include "GtkView.h"
#include "../../fs/FSHandler.h"

#include <iostream>
#include <string>

using namespace FileB;

GtkView::GtkView(const struct Settings& s) :
	View(s),
	cols(),
	model(Gtk::TreeStore::create(cols)),
	tree(new Gtk::TreeView(model))
{
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

GtkView::~GtkView() {}

void GtkView::showDir(Path path) {
	Directory const* dir = FSHandler::instance().listDir(path);
	model->clear();
	Gtk::TreeModel::Row row;
	for(std::vector<File*>::const_iterator i = dir->begin();
		i != dir->end(); i++)
		{
		// don't show . or ..
		if((*i)->isDot())
			continue;
		if(!settings.show_hidden && (*i)->isHidden())
			continue;
		row = *(model->append());
		row[cols.name] = *i;
	}
	vsettings.current_dir = dir;
}

void GtkView::onRowActivated(const Gtk::TreeModel::Path& p,
	Gtk::TreeViewColumn*)
	{
	Gtk::TreeModel::Row row = *(model->get_iter(p));
	File const* f = row.get_value(cols.name);
	Path path = f->getPath();
	// if it's a directory, show it
	if(dynamic_cast<Directory const*>(f))
		showDir(f->getPath());
	else
		std::cout << "opening file " << f->getName() << std::endl;
}

void GtkView::updateNameCol(Gtk::CellRenderer*,
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
		Glib::ustring text = Glib::locale_from_utf8(f->getName());
		cellrend_name.property_text() = text;
	}
}

void GtkView::updateContentCol(Gtk::CellRenderer*,
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
		Glib::ustring text;
		switch(f->getContent()) {
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
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
		// if it's a directory, don't display the size
		if(dynamic_cast<Directory const*>(f)) {
			cellrend_size.property_text() = "";
			return;
		}
		Glib::ustring text = Glib::locale_to_utf8(
			Application::getHumanReadableSize(f->getSize()));
		cellrend_size.property_text() = text;
	}
}

void GtkView::updateOwnerCol(Gtk::CellRenderer*,
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
		Glib::ustring text = Glib::locale_to_utf8(
			FSHandler::instance().getUserName(f->getOwner()));
		cellrend_owner.property_text() = text;
	}
}

void GtkView::updateGroupCol(Gtk::CellRenderer*,
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
		Glib::ustring text = Glib::locale_to_utf8(
			FSHandler::instance().getGroupName(f->getGroup()));
		cellrend_group.property_text() = text;
	}
}

void GtkView::updateMTimeCol(Gtk::CellRenderer*,
	const Gtk::TreeModel::iterator& i)
	{
	if(i) {
		File const* f = i->get_value(cols.name);
//		std::ostringstream s;
//		s << f->getMTime();
		Glib::ustring text = Glib::locale_to_utf8(
			Application::getHumanReadableTime(f->getMTime()));
		cellrend_mtime.property_text() = text;
	}
}

