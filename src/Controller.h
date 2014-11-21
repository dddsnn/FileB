#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "fs/File.h"

namespace FileB {
	class Controller {
	public:
		virtual ~Controller() {};
		virtual void onFileActivated(const File* f) = 0;
	};
}
#endif
