#ifndef SRC_FS_PATH_H_
#define SRC_FS_PATH_H_

#include <string>

namespace FileB {
class Directory;

/// A path in the filesystem.
class Path {
	public:
		Path();
		/// Constructs a path from a string.
		Path(const std::string path);
		/// Constructs a path from a directory and a name.
		Path(const Directory dir, std::string name);
		virtual ~Path();
		/// Removes all directory components of the file name.
		std::string getBaseName() const;
		/// Appends a file name to this path.
		void append(std::string name);
		/// Returns the path string encoded in the system's locale.
		std::string getPathString() const;
		/// Returns the depth of the path.
		unsigned int getDepth() const;
		/// Returns the name of a directory at a specific level.
		Path getLevel(unsigned int level) const;
	private:
		/// The path string encoded in the system's locale.
		std::string path;
};
}

#endif
