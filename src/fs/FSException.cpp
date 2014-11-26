#include "FSException.h"

#include <iostream>
using namespace FileB;

FileB::FSException::FSException(const std::string& msg) :
		msg(msg) {
}

FSException::~FSException() {
	// TODO Auto-generated destructor stub
}

const char* FileB::FSException::what() const noexcept {
	return msg.c_str();
}
