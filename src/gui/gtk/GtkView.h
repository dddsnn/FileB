#ifndef SRC_GUI_GTK_GTKVIEW_H_
#define SRC_GUI_GTK_GTKVIEW_H_

#include <gtkmm.h>
#include <list>

#include "../View.h"
#include "../../fs/Directory.h"

namespace FileB {
/// View using the Gtk+ toolkit.
class GtkView: public View, public Gtk::ScrolledWindow {

		/// ColumnRecord for the TreeView
		/**
		 * The file column is just here to keep a record of the file. Better
		 * way?
		 */
		class Columns: public Gtk::TreeModel::ColumnRecord {
			public:
				Columns() {
					add(name);
					add(content);
					add(size);
					add(owner);
					add(group);
					add(mtime);
					add(file);
				}

				Gtk::TreeModelColumn<std::string> name;
				Gtk::TreeModelColumn<int> content;
				Gtk::TreeModelColumn<off_t> size;
				Gtk::TreeModelColumn<uid_t> owner;
				Gtk::TreeModelColumn<gid_t> group;
				Gtk::TreeModelColumn<time_t> mtime;
				Gtk::TreeModelColumn<File*> file;
		};

	public:
		GtkView(Controller& c, ViewModel& model, int id);
		virtual ~GtkView();
		void update();
	private:
		Columns cols;
		Glib::RefPtr<Gtk::TreeStore> tree_model;
		Gtk::TreeView* tree;
		// cellrenderers and columns
		Gtk::CellRendererText cellrend_name, cellrend_content, cellrend_size,
				cellrend_owner, cellrend_group, cellrend_mtime;
		Gtk::TreeView::Column viewcol_name, viewcol_content, viewcol_size,
				viewcol_owner, viewcol_group, viewcol_mtime;
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
		void showFiles(const std::list<File*>& files);
		int compareNames(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		int compareContents(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		int compareSizes(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		int compareOwners(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		int compareGroups(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		int compareMTimes(const Gtk::TreeModel::iterator& a,
				const Gtk::TreeModel::iterator& b);
		static int compareInts(int a, int b);
};
}

#endif
