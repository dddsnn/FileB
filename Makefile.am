bin_PROGRAMS = fileb
fileb_CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic $(GTKMM_CFLAGS)
# TODO only include libmagic if needed
fileb_LDADD = $(GTKMM_LIBS) -lmagic
fileb_SOURCES = \
	src/Application.cpp \
	src/Observable.cpp \
	src/Observer.cpp \
	src/fs/Directory.cpp \
	src/fs/File.cpp \
	src/fs/FSException.cpp \
	src/fs/FSHandler.cpp \
	src/fs/Path.cpp \
	src/gui/MainWindow.cpp \
	src/gui/Pane.cpp \
	src/gui/View.cpp \
	src/gui/gtk/GtkMainWindow.cpp \
	src/gui/gtk/GtkPane.cpp \
	src/gui/gtk/GtkView.cpp \
	src/model/History.cpp \
	src/model/HistoryException.cpp \
	src/model/Model.cpp \
	src/model/ViewModel.cpp