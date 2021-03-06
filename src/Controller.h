#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "fs/File.h"

namespace FileB {
class Controller {
	public:
		virtual ~Controller(){}
		virtual void onFileActivated(const File* f) = 0;
		virtual void onBackBtnActivated() = 0;
		virtual void onForwardBtnActivated() = 0;
		virtual void onUpBtnActivated() = 0;
		virtual void onPathActivated(const Path& path)=0;
};
}
#endif
