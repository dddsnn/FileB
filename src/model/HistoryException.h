#ifndef SRC_MODEL_HISTORYEXCEPTION_H_
#define SRC_MODEL_HISTORYEXCEPTION_H_

#include <exception>
#include <string>

namespace FileB {
class HistoryException: public std::exception {
	public:
		HistoryException(const std::string& msg);
		virtual ~HistoryException();
		const char* what() const noexcept;
	private:
		const std::string msg;
};
}
#endif
