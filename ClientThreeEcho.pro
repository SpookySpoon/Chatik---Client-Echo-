QT += core
QT += network

CONFIG += c++11

TARGET = ClientTwo
CONFIG += console

CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    TcpMsgClient.cpp \
    chatwindow.cpp

HEADERS += \
    TcpMsgClient.h \
    chatwindow.h
