#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T23:23:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    proceso.cpp \
    lote.cpp \
    Visual/clock.cpp

HEADERS  += mainwindow.h \
    proceso.h \
    lote.h \
    Visual/clock.h

FORMS    += mainwindow.ui \
    Visual/clock.ui
CONFIG += c++11
