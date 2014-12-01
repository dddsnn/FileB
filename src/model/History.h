#ifndef SRC_MODEL_HISTORY_H_
#define SRC_MODEL_HISTORY_H_

#define MAX_HISTORY_ENTRIES 20

#include <deque>

#include "../fs/Path.h"

namespace FileB {
class History {
	public:
		History();
		virtual ~History();
		void addEntry(const Path& path);
		const Path& goBack();

	private:
		std::deque<Path> history;
		int back_steps;
};
}
#endif
