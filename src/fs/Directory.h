#ifndef SRC_FS_DIRECTORY_H_
#define SRC_FS_DIRECTORY_H_

#include <list>

#include "File.h"

namespace FileB {
class Path;

/// A directory entry that is itself a directory.
class Directory: public File, public std::list<File*> {
	public:
		Directory();
		/// Constructs a Directory from a path string.
		Directory(const Path path);
		/// Constructs a Directory from a Directory and a name.
		Directory(const Directory dir, std::string name);
		virtual ~Directory();
		/// Returns whether this Directory has been filled with Files.
		bool isComplete() const;
		/// Marks this directory as containing all its files.
		void markComplete();
	private:
		bool complete;
};
}

#endif
