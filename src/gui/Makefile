include ../Makefile.inc

SRC = ${wildcard *.cpp}
OBJ = ${SRC:%.cpp=%.o}
HDR = ${SRC:%.cpp=%.h}
SUBDIRS = gtk
SUBARS = ${addsuffix .a,${SUBDIRS}}
SUBCLEAN = ${addsuffix .clean,${SUBDIRS}}

all: gui.a

${SUBDIRS}:
	${MAKE} -C $@

gui.a: ${OBJ} ${SUBDIRS} ${SUBARS}
	${call bundle_ars,${SUBARS},${OBJ},../gui.a}

%.o: %.cpp %.h ${SUBARS}
	${CXX} ${CXXFLAGS} -c $< ${PRJLIBS}

clean: ${SUBCLEAN}
	rm -f ${OBJ} ${SUBARS}

${SUBCLEAN}:
	${MAKE} -C ${@:.clean=} clean

.PHONY: all clean ${SUBDIRS} ${SUBCLEAN}
