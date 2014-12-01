#ifndef SRC_MODEL_HISTORY_H_
#define SRC_MODEL_HISTORY_H_

#define MAX_HISTORY_ENTRIES 20

#include <deque>

#include "../fs/Path.h"
#include "HistoryException.h"

namespace FileB {
class History {
	public:
		History(const Path& path);
		virtual ~History();
		void addEntry(const Path& path);
		const Path& goBack();
		const Path& goForward();
		const Path& getCurrentPath() const;
		unsigned int getBackDepth();
		unsigned int getForwardDepth();

	private:
		std::deque<Path> history;
		unsigned int back_steps;
};
}
#endif
