#include "Observer.h"
#include "Observable.h"

using namespace FileB;

FileB::Observer::Observer(Observable* o) :
		observable(o) {
	observe(o);
}

Observer::~Observer() {
	if(observable) {
		observable->detach(this);
	}
}

void FileB::Observer::observe(Observable* o) {
	if(o) {
		observable = o;
		o->attach(this);
	}
}

void FileB::Observer::detach() {
	observable = 0;
}
