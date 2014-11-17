#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "globals.h"
#include "Controller.h"
#include "gui/gtk/GtkMainWindow.h"

#include <string>
#include <stdlib.h>

namespace FileB {
/// Main application.
class Application: public Controller {
	public:
		Application(int argc, char *args[]);
		/// Returns a human-readable file size.
		static std::string getHumanReadableSize(off_t size, int prefix);
		/// Returns a human-readable time.
		static std::string getHumanReadableTime(time_t time);
		virtual ~Application();
		enum {
			PREFIX_BASE_10, PREFIX_BASE_2
		};
		void openFile(File const* f);
	private:
		struct Settings settings;
		//GtkMainWindow mw;
};
}

#endif
