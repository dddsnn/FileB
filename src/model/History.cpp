#include "History.h"

using namespace FileB;

History::History() {
	// TODO Auto-generated constructor stub

}

History::~History() {
	// TODO Auto-generated destructor stub
}

void FileB::History::addEntry(const Path& path) {
	// if the current path isn't at the end, first erase following entries
	while(back_steps--) {
		history.pop_back();
	}
	history.push_back(path);
	if(history.size() > MAX_HISTORY_ENTRIES)
		history.pop_front();
}

const Path& FileB::History::goBack() {
	if(!back_steps < history.size() - 1) {
		throw std::exception(); //TODO
	}
	back_steps++;
	return history.at(history.size() - back_steps - 1);
}
