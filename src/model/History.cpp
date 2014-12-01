#include "History.h"

using namespace FileB;

History::History(const Path& path) :
		history(), back_steps(0) {
	history.push_back(path);
}

History::~History() {
	// TODO Auto-generated destructor stub
}

void FileB::History::addEntry(const Path& path) {
	// if the current path isn't at the end, first erase following entries
	while(back_steps) {
		history.pop_back();
		back_steps--;
	}
	history.push_back(path);
	if(history.size() > MAX_HISTORY_ENTRIES)
		history.pop_front();
}

const Path& FileB::History::goBack() {
	if(!(back_steps < history.size() - 1)) {
		throw HistoryException("No more history to go back to");
	}
	back_steps++;
	return getCurrentPath();
}

const Path& FileB::History::goForward() {
	if(back_steps == 0) {
		throw HistoryException("No history to go forward to");
	}
	back_steps--;
	return getCurrentPath();
}

const Path& FileB::History::getCurrentPath() const {
	return history.at(history.size() - back_steps - 1);
}

unsigned int FileB::History::getBackDepth() {
	return history.size() - back_steps - 1;
}

unsigned int FileB::History::getForwardDepth() {
	return back_steps;
}
