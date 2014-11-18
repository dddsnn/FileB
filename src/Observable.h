#ifndef SRC_OBSERVABLE_H_
#define SRC_OBSERVABLE_H_

#include <deque>

#include "Observer.h"

namespace FileB {

class Observable {
	public:
		Observable();
		virtual ~Observable();
		void notify();
		void attach(Observer* o);
		void detach(Observer* o);

	private:
		std::deque<Observer*> observers;
};
}

#endif
