# -------------------------------------------------
# Project created by QtCreator 2010-03-26T17:44:17
# -------------------------------------------------
QT += network \
      dbus

QT -= gui
#CONFIG += debug
#CONFIG += crypto
CONFIG += QOAUTH
TARGET   = desktop-couch-qt
TEMPLATE = lib
DEFINES += DESKTOPCOUCHDBQT_LIBRARY

#LIBS += /usr/lib/libqoauth.so
LIBS += /usr/lib/libgnome-keyring.so
LIBS += ../libs/libcouchdb-qt.so
INCLUDEPATH += ../couchdb-qt
INCLUDEPATH += /usr/include/glib-2.0 /usr/lib/glib-2.0/include
INCLUDEPATH += /usr/include/gnome-keyring-1
INCLUDEPATH += /usr/include/QtCrypto/

SOURCES += desktop_couch.cpp
HEADERS += desktop_couch.h

DESTDIR      = ../libs
OBJECTS_DIR  = objects
RCC_DIR      = sources


target.path = /usr/lib

headers.files += desktop_couch.h
headers.path = /usr/include/desktop-couch-qt
INSTALLS += target  \
            headers
