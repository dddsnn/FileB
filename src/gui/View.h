#ifndef SRC_GUI_VIEW_H_
#define SRC_GUI_VIEW_H_

#include <string>
#include <list>

#include "../globals.h"
#include "../Controller.h"
#include "../fs/Path.h"
#include "ViewModel.h"
#include "../Observer.h"

namespace FileB {
//	struct ViewSettings {
//		std::vector<int[2]> cols;
//		Directory const* current_dir;
//	};

/// Abstract class for the part of the UI that displays directories.
/**
 * This class should be subclassed implementing an actual window with
 * a specific toolkit.
 */
class View : public Observer {
	public:
		virtual ~View();
		/// Displays a directory in this View.
		virtual void showFiles(const std::list<File*>& files) = 0;
		virtual void update() = 0;
		ViewModel& getModel();

	protected:
		View(Controller& c);
		Controller& controller;
//		enum {
//			ORDER_ASCENDING,
//			ORDER_DESCENDING,
//			COLUMN_NAME,
//			COLUMN_TYPE,
//			COLUMN_SIZE
//		};
		ViewModel model;
};
}

#endif
