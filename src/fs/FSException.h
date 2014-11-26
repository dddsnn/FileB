#ifndef SRC_FS_FSEXCEPTION_H_
#define SRC_FS_FSEXCEPTION_H_

#include <exception>
#include <string>

namespace FileB {
class FSException: public std::exception {
	public:
		FSException(const std::string& msg);
		virtual ~FSException();
		const char* what() const noexcept;
	private:
		const std::string msg;
};
}
#endif
