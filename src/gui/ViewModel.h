#ifndef SRC_GUI_VIEWMODEL_H_
#define SRC_GUI_VIEWMODEL_H_

#include "../fs/Directory.h"
#include "../Observable.h"

namespace FileB {

// TODO do i need a view specific separate representation for File?
//struct FileEntry {
//		std::string name;
//		int type;
//		int content;
//		uid_t owner;
//		gid_t group;
//		off_t size;
//		time_t mtime;
//};

class ViewModel : public Observable {
	public:
		ViewModel();
		virtual ~ViewModel();
		const std::list<File*>* getCurrentFiles() const;
		void showDir(const Path& path);

	private:
		const std::list<File*>* current_files;
};
}
#endif
