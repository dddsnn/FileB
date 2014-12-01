#include "HistoryException.h"
#include <iostream>
using namespace FileB;

FileB::HistoryException::HistoryException(const std::string& msg) :
		msg(msg) {
}

HistoryException::~HistoryException() {
	// TODO Auto-generated destructor stub
}

const char* FileB::HistoryException::what() const noexcept {
	return msg.c_str();
}
