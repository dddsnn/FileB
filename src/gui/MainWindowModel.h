#ifndef SRC_GUI_MAINWINDOWMODEL_H_
#define SRC_GUI_MAINWINDOWMODEL_H_

#include "../fs/Path.h"
#include "../Observable.h"

namespace FileB {
class MainWindowModel: public Observable {
	public:
		MainWindowModel();
		virtual ~MainWindowModel();
		void showPath(Path path);
		const Path& getCurrentPath() const;

	private:
		Path current_path;
};
}
#endif
