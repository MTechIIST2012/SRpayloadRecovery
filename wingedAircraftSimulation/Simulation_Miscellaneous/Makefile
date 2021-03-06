#############################################################################
# Makefile for building: libSimulation_Miscellaneous.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.8.1) on: Tue May 28 14:22:55 2013
# Project:  Simulation_Miscellaneous.pro
# Template: lib
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile Simulation_Miscellaneous.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DSIMULATION_MISCELLANEOUS_LIBRARY -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4 -I../common -I.
LINK          = g++
LFLAGS        = -m64 -shared -Wl,-soname,libSimulation_Miscellaneous.so.1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = linearchara.cpp \
		nonlinearchara.cpp \
		virtualportmaker.cpp moc_virtualportmaker.cpp
OBJECTS       = linearchara.o \
		nonlinearchara.o \
		virtualportmaker.o \
		moc_virtualportmaker.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Simulation_Miscellaneous.pro
QMAKE_TARGET  = Simulation_Miscellaneous
DESTDIR       = ../bin/debug/
TARGET        = libSimulation_Miscellaneous.so.1.0.0
TARGETA       = ../bin/debug/libSimulation_Miscellaneous.a
TARGETD       = libSimulation_Miscellaneous.so.1.0.0
TARGET0       = libSimulation_Miscellaneous.so
TARGET1       = libSimulation_Miscellaneous.so.1
TARGET2       = libSimulation_Miscellaneous.so.1.0

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  ../bin/debug/$(TARGET)

../bin/debug/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) ../bin/debug/ || $(MKDIR) ../bin/debug/ 
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)
	-$(DEL_FILE) ../bin/debug/$(TARGET)
	-$(DEL_FILE) ../bin/debug/$(TARGET0)
	-$(DEL_FILE) ../bin/debug/$(TARGET1)
	-$(DEL_FILE) ../bin/debug/$(TARGET2)
	-$(MOVE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2) ../bin/debug/
	{ test -z "$(DESTDIR)" || cd "$(DESTDIR)"; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index ." -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

Makefile: Simulation_Miscellaneous.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile Simulation_Miscellaneous.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++-64 CONFIG+=debug -o Makefile Simulation_Miscellaneous.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Simulation_Miscellaneous1.0.0 || $(MKDIR) .tmp/Simulation_Miscellaneous1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Simulation_Miscellaneous1.0.0/ && $(COPY_FILE) --parents Simulation_Miscellaneous_global.h ICharacteristics.h linearchara.h nonlinearchara.h virtualportmaker.h .tmp/Simulation_Miscellaneous1.0.0/ && $(COPY_FILE) --parents linearchara.cpp nonlinearchara.cpp virtualportmaker.cpp .tmp/Simulation_Miscellaneous1.0.0/ && (cd `dirname .tmp/Simulation_Miscellaneous1.0.0` && $(TAR) Simulation_Miscellaneous1.0.0.tar Simulation_Miscellaneous1.0.0 && $(COMPRESS) Simulation_Miscellaneous1.0.0.tar) && $(MOVE) `dirname .tmp/Simulation_Miscellaneous1.0.0`/Simulation_Miscellaneous1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Simulation_Miscellaneous1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) ../bin/debug/$(TARGET) 
	-$(DEL_FILE) ../bin/debug/$(TARGET0) ../bin/debug/$(TARGET1) ../bin/debug/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_virtualportmaker.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_virtualportmaker.cpp
moc_virtualportmaker.cpp: virtualportmaker.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) virtualportmaker.h -o moc_virtualportmaker.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

linearchara.o: linearchara.cpp linearchara.h \
		ICharacteristics.h \
		Simulation_Miscellaneous_global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o linearchara.o linearchara.cpp

nonlinearchara.o: nonlinearchara.cpp nonlinearchara.h \
		ICharacteristics.h \
		Simulation_Miscellaneous_global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nonlinearchara.o nonlinearchara.cpp

virtualportmaker.o: virtualportmaker.cpp virtualportmaker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o virtualportmaker.o virtualportmaker.cpp

moc_virtualportmaker.o: moc_virtualportmaker.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_virtualportmaker.o moc_virtualportmaker.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

