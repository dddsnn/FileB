#ifndef GTKVIEW_H
#define GTKVIEW_H

#include <gtkmm.h>

#include "../View.h"
#include "../../fs/Directory.h"

namespace FileB {
	/// View using the Gtk+ toolkit.
	class GtkView : public View, public Gtk::Alignment {

		/// ColumnRecord for the TreeView
		/**
		 * The name column must always be added because it's the only
		 * one holding actual data.
		 * Is there a better way to do this? I want to store files.
		 */
		class Columns : public Gtk::TreeModel::ColumnRecord {
		public:
			Columns() {
				add(name);
				add(content);
				add(size);
				add(owner);
				add(group);
				add(mtime);
			}

			Gtk::TreeModelColumn<File const*> name;
			Gtk::TreeModelColumn<int> content;
			Gtk::TreeModelColumn<int> size;
			Gtk::TreeModelColumn<int> owner;
			Gtk::TreeModelColumn<int> group;
			Gtk::TreeModelColumn<int> mtime;
		};

	public:
		GtkView(const struct Settings& s);
		virtual ~GtkView();
		void showDir(Path path);
	private:
		Columns cols;
		Glib::RefPtr<Gtk::TreeStore> model;
		Gtk::TreeView* tree;
		// cellrenderers and columns
		Gtk::CellRendererText cellrend_name,
			cellrend_content,
			cellrend_size,
			cellrend_owner,
			cellrend_group,
			cellrend_mtime;
		Gtk::TreeView::Column viewcol_name,
			viewcol_content,
			viewcol_size,
			viewcol_owner,
			viewcol_group,
			viewcol_mtime;
		/// Signal handler for opening a file/directory.
		void onRowActivated(const Gtk::TreeModel::Path& path,
			Gtk::TreeViewColumn*);
		/// Signal handler for updating the name column.
		void updateNameCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
		/// Signal handler for updating the content column.
		void updateContentCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
		/// Signal handler for updating the size column.
		void updateSizeCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
		/// Signal handler for updating the owner column.
		void updateOwnerCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
		/// Signal handler for updating the group column.
		void updateGroupCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
		/// Signal handler for updating the mtime column.
		void updateMTimeCol(Gtk::CellRenderer*,
			const Gtk::TreeModel::iterator& i);
	};
}

#endif
