# -------------------------------------------------
# Project created by QtCreator 2010-03-26T17:44:17
# -------------------------------------------------
QT += network #\
      #dbus
QT -= gui

#CONFIG += debug
#CONFIG += crypto #sometimes this definition works sometimes not.
CONFIG += QOAUTH

TARGET   = couchdb-qt
TEMPLATE = lib
DEFINES += COUCHDBQT_LIBRARY
INCLUDEPATH += /usr/include/qjson/
INCLUDEPATH += /usr/include/QtCrypto/


LIBS += /usr/lib/libqoauth.so
LIBS += /usr/lib/libqjson.so

SOURCES += couchdbqtchangenotifier.cpp \
           couchdb-qt.cpp \
           auth_info.cpp

HEADERS += couchdbqtchangenotifier.h \
           couchdb-qt.h \
           auth_info.h \


OBJECTS_DIR  = objects
RCC_DIR      = sources
DESTDIR      = ../libs

target.path = /usr/lib
headers.files = couchdbqtchangenotifier.h \
                couchdb-qt.h \
                auth_info.h
headers.path = /usr/include/couchdb-qt
INSTALLS += target \
            headers

