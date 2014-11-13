#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <stdlib.h>

namespace FileB {
	/// Global Settings
	struct Settings {
		/// whether or not to show hidden files
		bool show_hidden;
		/// prefix for file sizes (kB vs. KiB)
		int prefix;
	};
	
	/// Main application.
	class Application {
	public:
		Application(int argc, char *args[]);
		/// Returns a human-readable file size.
		static std::string getHumanReadableSize(off_t size);
		/// Returns a human-readable time.
		static std::string getHumanReadableTime(time_t time);
		virtual ~Application();
		enum {
			PREFIX_BASE_10,
			PREFIX_BASE_2
		};
	private:
		static struct Settings settings;
	};
}

#endif
