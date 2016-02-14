#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T20:57:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Modelo/genera_procesos.cpp \
    Visual/clock.cpp \
    dialogosimulacion.cpp \
    lote.cpp \
    proceso.cpp \
    Modelo/simulasistemaoperativo.cpp \
    Visual/dialogotiempos.cpp

HEADERS  += mainwindow.h \
    Modelo/genera_procesos.h \
    Visual/clock.h \
    dialogosimulacion.h \
    lote.h \
    proceso.h \
    Visual/dialogotiempos.h \
    Modelo/simulasistemaoperativo.h

FORMS    += mainwindow.ui \
    Visual/clock.ui \
    dialogosimulacion.ui \
    Visual/dialogotiempos.ui
CONFIG += c++11
