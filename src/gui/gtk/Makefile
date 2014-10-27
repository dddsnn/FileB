include ../../Makefile.inc

SRC = ${wildcard *.cpp}
OBJ = ${SRC:%.cpp=%.o}
HDR = ${SRC:%.cpp=%.h}
SUBDIRS =
SUBARS = ${addsuffix .a,${SUBDIRS}}
SUBCLEAN = ${addsuffix .clean,${SUBDIRS}}

all: gtk.a

${SUBDIRS}:
	${MAKE} -C $@

gtk.a: ${OBJ} ${SUBDIRS} ${SUBARS}
	${call bundle_ars,${SUBARS},${OBJ},../gtk.a}

%.o: %.cpp %.h ${SUBARS}
	${CXX} ${CXXFLAGS} -c $< ${PRJLIBS} ${GTKLIBS}

clean: ${SUBCLEAN}
	rm -f ${OBJ} ${SUBARS}

${SUBCLEAN}:
	${MAKE} -C ${@:.clean=} clean

.PHONY: all clean ${SUBDIRS} ${SUBCLEAN}
