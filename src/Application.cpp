#include "Application.h"
#include "fs/Path.h"
#include "fs/FSHandler.h"

#include <gtkmm.h>
#include <iostream>

using namespace FileB;

//struct Settings Application::settings;

/// Starts the application.
Application::Application(int argc, char *args[]) :
		gtk_app(
				Gtk::Application::create(argc, args, Glib::ustring(),
						Gio::APPLICATION_FLAGS_NONE)), mw(*this) {
	mw.fullscreen();
	gtk_app->run(mw);
}

Application::~Application() {
}

int main(int argc, char *args[]) {
	Application(argc, args);
	return EXIT_SUCCESS;
}

std::string Application::getHumanReadableSize(off_t size, int prefix) {
	int div = 1000;
	int count = 0;
	std::string res;
	switch(prefix) {
	case Application::PREFIX_BASE_10:
		div = 1000;
		break;
	case Application::PREFIX_BASE_2:
		div = 1024;
		break;
	}
	if(size >= div * div) {
		size /= div;
		count++;
		size *= 10;
	} else if(size >= div) {
		size *= 10;
		size /= div;
		count++;
	} else {
		size *= 10;
	}
	while(size >= div * 10) {
		size /= div;
		count++;
	}
	float f = static_cast<float>(size);
	f /= 10;
	std::ostringstream s;
	s << f;
	res = s.str();
	switch(prefix) {
	case Application::PREFIX_BASE_10:
		switch(count) {
		case 0:
			res.append(" B");
			break;
		case 1:
			res.append(" KB");
			break;
		case 2:
			res.append(" MB");
			break;
		case 3:
			res.append(" GB");
			break;
		case 4:
			res.append(" TB");
			break;
		case 5:
			res.append(" PB");
			break;
		case 6:
			res.append(" EB");
			break;
		default:
			res = std::string("really, really big");
		}
		break;
	case Application::PREFIX_BASE_2:
		switch(count) {
		case 0:
			res.append(" B");
			break;
		case 1:
			res.append(" KiB");
			break;
		case 2:
			res.append(" MiB");
			break;
		case 3:
			res.append(" GiB");
			break;
		case 4:
			res.append(" TiB");
			break;
		case 5:
			res.append(" PiB");
			break;
		case 6:
			res.append(" EiB");
			break;
		default:
			res = std::string("really, really big");
		}
	}
	return res;
}

std::string Application::getHumanReadableTime(time_t time) {
	struct tm tm;
	if(!localtime_r(&time, &tm))
		return std::string();
	char* s = new char[40];
	struct tm const* tm_p = &tm;
	if(!strftime(s, 40, "%x %X", tm_p))
		return std::string();
	std::string res(s);
	delete[] s;
	return res;
}

void FileB::Application::onFileActivated(const File* f) {
	// if it's a directory, show it
	const Directory* dir = dynamic_cast<const Directory*>(f);
	if(dir) {
		mw.getActiveView().getModel().showDir(dir->getPath());
		mw.getModel().showPath(dir->getPath());
	} else
		std::cout << "opening file " << f->getName() << std::endl;
}
