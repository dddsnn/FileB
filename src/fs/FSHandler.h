#ifndef SRC_FS_FSHANDLER_H_
#define SRC_FS_FSHANDLER_H_

#include <list>
#include <string>
#include <dirent.h>

#include "File.h"
#include "Directory.h"

namespace FileB {
/// Singleton class to handle all low-level file operations.
class FSHandler {
	public:
		/// Returns the instance of this singleton. 
		static FSHandler& instance();
		/// Gets the Directory represented by a Path.
		const Directory* listDir(const Path path);
		/// Matches a user name to a uid.
		std::string getUserName(uid_t uid) const;
		/// Matches a group name to a gid.
		std::string getGroupName(gid_t gid) const;
	private:
		FSHandler();
		FSHandler(const FSHandler&);
		FSHandler& operator=(const FSHandler&);
		~FSHandler();
		/// Gets the directory but doesn't fill it with files.
		Directory* getDir(const Path path);
		/// Wrapper for opendir that includes error handling.
		DIR* safeOpenDir(const Path path);
		/// Wrapper for closedir that includes error handling.
		void safeCloseDir(DIR* dir);
		/// Fills f with file information.
		void safeStat(File* f);
		static FSHandler* m_instance;
		Directory* root;
};
}

#endif
