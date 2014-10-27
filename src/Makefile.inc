CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic
LD = g++
LDFLAGS =
AR = ar
# gtk as project wide lib for testing purposes. should be removed later
PRJLIBS = `pkg-config gtkmm-3.0 --cflags --libs`
GTKLIBS = `pkg-config gtkmm-3.0 --cflags --libs`

# function to be called with call
# ${call bundle_ars,ars,objs,output}
# ars       ars to be bundled
# objs      new .o to be added
# output    single output ar
bundle_ars = ${if ${1},mkdir _tmp_objects_ ; cd _tmp_objects_ ; \
    ${foreach archive,${addprefix ../,${1}},${AR} -x ${archive} ;} cd .. ; \
    ${AR} -cr ${3} _tmp_objects_/*.o ${2} ; rm -rf _tmp_objects_,\
    ${AR} -cr ${3} ${2}}
