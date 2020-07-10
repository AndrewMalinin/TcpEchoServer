QT += core
QT += network
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include $$PWD/src

HEADERS +=  include/settingparser.h \
            include/tcpserver.h

SOURCES += src/main.cpp \
        src/settingparser.cpp \
        src/tcpserver.cpp

MOC_DIR = $$PWD/moc
OBJECTS_DIR = $$PWD/obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
