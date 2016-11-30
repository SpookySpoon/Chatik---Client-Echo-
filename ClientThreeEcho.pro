QT += core
QT += network
QT += widgets


CONFIG += c++11

TARGET = ClientTwo
CONFIG += console

CONFIG -= app_bundle

TEMPLATE = app

win32:INCLUDEPATH += "D:\Games\protobuf1\src"

SOURCES += main.cpp \
    chatwindow.cpp \
    tcpmsgclient.cpp \
    chatclient.cpp \
    messageformat.pb.cc

HEADERS += \
    chatwindow.h \
    tcpmsgclient.h \
    chatclient.h \
    messageformat.pb.h \
    protobytes.h

#LIBS += -lprotobuf
#LIBS += -LD:\Games\MSYS2\mingw64\lib -lprotobuf

#LIBS += -l $$PWD

#PROTOS = a.proto b.proto
#include(protobuf.pri)

#DISTFILES += \
#    protobuf.pri

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Games/protobuf1/src/.libs/ -lprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Games/protobuf1/src/.libs/ -lprotobuf

INCLUDEPATH += $$PWD/../../../../../Games/protobuf1/src/.libs
DEPENDPATH += $$PWD/../../../../../Games/protobuf1/src/.libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../Games/protobuf1/src/.libs/libprotobuf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../Games/protobuf1/src/.libs/libprotobuf.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../Games/protobuf1/src/.libs/protobuf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../Games/protobuf1/src/.libs/protobuf.lib
