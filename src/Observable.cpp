#include "Observable.h"

using namespace FileB;

Observable::Observable() {
	// TODO Auto-generated constructor stub

}

Observable::~Observable() {
	for(std::deque<Observer*>::iterator i = observers.begin();
			i != observers.end(); i++) {
		(*i)->detach();
	}
}

void Observable::notify() {
	for(std::deque<Observer*>::iterator i = observers.begin();
			i != observers.end(); i++) {
		(*i)->update();
	}
}

void FileB::Observable::attach(Observer* o) {
	// TODO passing 0 is a nop
	if(o) {
		observers.push_back(o);
	}
}

void FileB::Observable::detach(Observer* o) {
	for(std::deque<Observer*>::iterator i = observers.begin();
			i != observers.end(); i++) {
		if(*i == o) {
			observers.erase(i);
			break;
		}
	}
}
