include Makefile.inc

SRC = ${wildcard *.cpp}
OBJ = ${SRC:%.cpp=%.o}
HDR = ${SRC:%.cpp=%.h}
SUBDIRS = fs gui
SUBARS = ${addsuffix .a,${SUBDIRS}}
SUBCLEAN = ${addsuffix .clean,${SUBDIRS}}

all: FileB doc

${SUBDIRS}:
	${MAKE} -C $@

FileB: ${SUBDIRS} ${SUBARS} ${OBJ}
	${call bundle_ars,${SUBARS},${OBJ},all.a}
	${LD} ${LDFLAGS} -o ../FileB all.a ${PRJLIBS}

%.o: %.cpp %.h ${SUBARS}
	${CXX} ${CXXFLAGS} -c $< ${PRJLIBS}

doc: ${OBJ} doxygen_config
	doxygen doxygen_config

clean: ${SUBCLEAN}
	rm -f ../FileB ${OBJ} ${SUBARS}

${SUBCLEAN}:
	${MAKE} -C ${@:.clean=} clean

.PHONY: all clean ${SUBDIRS} ${SUBCLEAN}
