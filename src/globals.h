#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

namespace FileB {
	/// Global Settings
	struct Settings {
		/// whether or not to show hidden files
		bool show_hidden;
		/// prefix for file sizes (kB vs. KiB)
		int prefix;
	};
}

#endif
