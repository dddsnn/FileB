#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>

#include "../Application.h"
#include "../fs/Path.h"

namespace FileB {
	struct ViewSettings {
		std::vector<int[2]> cols;
		Directory const* current_dir;
	};

	/// Abstract class for the part of the UI that displays directories.
	/**
	 * This class should be subclassed implementing an actual window with
	 * a specific toolkit.
	 */
	class View {
	public:
		virtual ~View();
		/// Displays a directory in this View.
		virtual void showDir(Path path) = 0;
	protected:
		View(const struct Settings& s);
		const struct Settings settings;
		enum {
			ORDER_ASCENDING,
			ORDER_DESCENDING,
			COLUMN_NAME,
			COLUMN_TYPE,
			COLUMN_SIZE
		};
		struct ViewSettings vsettings;
	};
}

#endif
