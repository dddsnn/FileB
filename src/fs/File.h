#ifndef FILE_H
#define FILE_H

#include <string>

#include "Path.h"

namespace FileB {
	class Directory;

	/// A directory entry.
	class File {
	public:
		File();
		/// Constructs a File from a path.
		File(const Path path, int type = TYPE_UNKNOWN);
		/// Constructs a File from a directory and a name.
		File(const Directory dir, std::string name,
			int type = TYPE_UNKNOWN);
		virtual ~File();
		/// Returns the name of this File.
		const std::string getName() const;
		/// Returns the full path of this File.
		const Path getPath() const;
		/// Tests whether this file is . or ..
		bool isDot() const;
		/// Tests whether this File is hidden.
		bool isHidden() const;
		int getType() const;
		void setType(int type);
		int getContent() const;
		void setContent(int content);
		uid_t getOwner() const;
		void setOwner(uid_t owner);
		gid_t getGroup() const;
		void setGroup(gid_t group);
		off_t getSize() const;
		void setSize(off_t size);
		time_t getMTime() const;
		void setMTime(time_t time);
//		virtual  void asd();
		enum Type {
			TYPE_UNKNOWN,
			TYPE_REGULAR,
			TYPE_DIRECTORY,
			TYPE_FIFO,
			TYPE_SOCKET,
			TYPE_CHAR,
			TYPE_BLOCK,
			TYPE_LINK,
			TYPE_MSGQ,
			TYPE_SEM,
			TYPE_SHMEM,
			CONTENT_UNKNOWN,
			CONTENT_DIRECTORY
		};
	protected:
		Path path;
		int type;
		int content;
		uid_t owner;
		gid_t group;
		off_t size;
		time_t mtime;
	};
}

#endif
