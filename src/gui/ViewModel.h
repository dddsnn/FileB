#ifndef SRC_GUI_VIEWMODEL_H_
#define SRC_GUI_VIEWMODEL_H_

#include "../fs/Directory.h"

namespace FileB {

struct FileEntry {
	std::string name;
};

class ViewModel {
	public:
		ViewModel();
		virtual ~ViewModel();
		const Directory* getCurrentDir() const;

	private:
		//std::vector<int[2]> cols;
		Directory const* current_dir;
};
}
#endif
