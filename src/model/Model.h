#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../fs/Path.h"
#include "../Observable.h"
#include "ViewModel.h"

#include <map>

namespace FileB {
class Model: public Observable {
	public:
		Model();
		virtual ~Model();
		void activatePath(const Path& path);
		void showPreviousPath();
		void showNextPath();
		const Path& getCurrentPath() const;
		void addViewModel(int id, ViewModel* view_model);
		bool hasBackHistory();
		bool hasForwardHistory();

	private:
		int active_view_id;
		std::map<int, ViewModel*> view_models;
		Path current_path;
		void showPath(const Path& path);
};
}
#endif
