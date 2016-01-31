#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T18:39:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogosimulacion.cpp \
    lote.cpp \
    proceso.cpp \
    Visual/clock.cpp

HEADERS  += mainwindow.h \
    dialogosimulacion.h \
    lote.h \
    proceso.h \
    Visual/clock.h

FORMS    += mainwindow.ui \
    dialogosimulacion.ui \
    Visual/clock.ui
CONFIG += c++11

DISTFILES += \
    P2.pro.user

