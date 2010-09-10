QT += network #\
      #dbus
QT -= gui
TARGET   = QLog
TEMPLATE = lib



SOURCES += QLog.cpp
HEADERS += QLog.h

OBJECTS_DIR  = objects
RCC_DIR      = sources
DESTDIR      = ../libs

target.path = /usr/lib
headers.files = QLog.h
headers.path = /usr/include/QLog
INSTALLS += target \
            headers
