#include "ViewModel.h"

using namespace FileB;

ViewModel::ViewModel() : current_dir() {
	// TODO Auto-generated constructor stub

}

ViewModel::~ViewModel() {
	// TODO Auto-generated destructor stub
}

const Directory* ViewModel::getCurrentDir() const {
	return current_dir;
}
