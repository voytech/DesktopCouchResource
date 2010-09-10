# -------------------------------------------------
# Project created by QtCreator 2010-03-26T17:44:17
# -------------------------------------------------
QT += network #\
      #dbus
QT -= gui
#CONFIG += debug
#CONFIG += crypto
TARGET   = tests
TEMPLATE = app


LIBS  += ../libs/libdesktop-couch-qt.so
LIBS  += ../libs/libcouchdb-qt.so
LIBS  += ../libs/libQLog.so
#LIBS  += /usr/lib/libdesktop-couch-qt.so
#LIBS  += /usr/lib/libcouchdb-qt.so
#LIBS +=  /usr/lib/libqjson.so
#INCLUDEPATH += /usr/include/couchdb-qt /usr/include/desktop-couch-qt
INCLUDEPATH += /usr/include/qjson/
INCLUDEPATH += ../couchdb-qt ../desktop-couch-qt ../QLog /usr/include/qjson/
INCLUDEPATH += /usr/include/glib-2.0 /usr/lib/glib-2.0/include
INCLUDEPATH += /usr/include/QtCrypto/

SOURCES += cmdline_tester.cpp



DESTDIR      = output
OBJECTS_DIR  = objects
RCC_DIR      = sources
