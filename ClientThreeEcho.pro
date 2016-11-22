QT += core
QT += network
QT += widgets

CONFIG += c++11

TARGET = ClientTwo
CONFIG += console

CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    c3echosession.cpp \
    c3echo.cpp

HEADERS += \
    c3echosession.h \
    c3echo.h
