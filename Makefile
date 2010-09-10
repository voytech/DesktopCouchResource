#############################################################################
# Makefile for building: desktop-couch-resource
# Generated by qmake (2.01a) (Qt 4.6.2) on: czw. wrz 9 09:13:06 2010
# Project:  desktop_couch_resource.pro
# Template: subdirs
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile desktop_couch_resource.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake-qt4
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-couchdb-qt \
		sub-QLog \
		sub-desktop-couch-qt \
		sub-tests

couchdb-qt//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) couchdb-qt/ || $(MKDIR) couchdb-qt/ 
	cd couchdb-qt/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/couchdb-qt/couchdb-qt.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-couchdb-qt-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) couchdb-qt/ || $(MKDIR) couchdb-qt/ 
	cd couchdb-qt/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/couchdb-qt/couchdb-qt.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-couchdb-qt: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE)
sub-couchdb-qt-make_default: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) 
sub-couchdb-qt-make_first: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) first
sub-couchdb-qt-all: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) all
sub-couchdb-qt-clean: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) clean
sub-couchdb-qt-distclean: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) distclean
sub-couchdb-qt-install_subtargets: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) install
sub-couchdb-qt-uninstall_subtargets: couchdb-qt//$(MAKEFILE) FORCE
	cd couchdb-qt/ && $(MAKE) -f $(MAKEFILE) uninstall
QLog//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) QLog/ || $(MKDIR) QLog/ 
	cd QLog/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/QLog/QLog.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-QLog-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) QLog/ || $(MKDIR) QLog/ 
	cd QLog/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/QLog/QLog.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-QLog: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE)
sub-QLog-make_default: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) 
sub-QLog-make_first: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) first
sub-QLog-all: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) all
sub-QLog-clean: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) clean
sub-QLog-distclean: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) distclean
sub-QLog-install_subtargets: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) install
sub-QLog-uninstall_subtargets: QLog//$(MAKEFILE) FORCE
	cd QLog/ && $(MAKE) -f $(MAKEFILE) uninstall
desktop-couch-qt//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) desktop-couch-qt/ || $(MKDIR) desktop-couch-qt/ 
	cd desktop-couch-qt/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/desktop-couch-qt/desktop-couch-qt.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-desktop-couch-qt-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) desktop-couch-qt/ || $(MKDIR) desktop-couch-qt/ 
	cd desktop-couch-qt/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/desktop-couch-qt/desktop-couch-qt.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-desktop-couch-qt: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE)
sub-desktop-couch-qt-make_default: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) 
sub-desktop-couch-qt-make_first: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) first
sub-desktop-couch-qt-all: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) all
sub-desktop-couch-qt-clean: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) clean
sub-desktop-couch-qt-distclean: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) distclean
sub-desktop-couch-qt-install_subtargets: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) install
sub-desktop-couch-qt-uninstall_subtargets: desktop-couch-qt//$(MAKEFILE) FORCE
	cd desktop-couch-qt/ && $(MAKE) -f $(MAKEFILE) uninstall
tests//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) tests/ || $(MKDIR) tests/ 
	cd tests/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/tests/tests.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-tests-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) tests/ || $(MKDIR) tests/ 
	cd tests/ && $(QMAKE) /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/tests/tests.pro -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-tests: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE)
sub-tests-make_default: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) 
sub-tests-make_first: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) first
sub-tests-all: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) all
sub-tests-clean: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) clean
sub-tests-distclean: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) distclean
sub-tests-install_subtargets: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) install
sub-tests-uninstall_subtargets: tests//$(MAKEFILE) FORCE
	cd tests/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: desktop_couch_resource.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile desktop_couch_resource.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile desktop_couch_resource.pro

qmake_all: sub-couchdb-qt-qmake_all sub-QLog-qmake_all sub-desktop-couch-qt-qmake_all sub-tests-qmake_all FORCE

make_default: sub-couchdb-qt-make_default sub-QLog-make_default sub-desktop-couch-qt-make_default sub-tests-make_default FORCE
make_first: sub-couchdb-qt-make_first sub-QLog-make_first sub-desktop-couch-qt-make_first sub-tests-make_first FORCE
all: sub-couchdb-qt-all sub-QLog-all sub-desktop-couch-qt-all sub-tests-all FORCE
clean: sub-couchdb-qt-clean sub-QLog-clean sub-desktop-couch-qt-clean sub-tests-clean FORCE
distclean: sub-couchdb-qt-distclean sub-QLog-distclean sub-desktop-couch-qt-distclean sub-tests-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-couchdb-qt-install_subtargets sub-QLog-install_subtargets sub-desktop-couch-qt-install_subtargets sub-tests-install_subtargets FORCE
uninstall_subtargets: sub-couchdb-qt-uninstall_subtargets sub-QLog-uninstall_subtargets sub-desktop-couch-qt-uninstall_subtargets sub-tests-uninstall_subtargets FORCE

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

