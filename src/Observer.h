#ifndef SRC_OBSERVER_H_
#define SRC_OBSERVER_H_

namespace FileB {
class Observable;

class Observer {
	public:
		Observer();
		Observer(Observable* o);
		virtual ~Observer();
		virtual void update() = 0;
		void observe(Observable* o);
		void detach();

	private:
		Observable* observable;
};
}

#endif
