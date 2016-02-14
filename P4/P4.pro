#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T15:13:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Modelo/genera_procesos.cpp \
    Modelo/simulasistemaoperativo.cpp \
    Visual/clock.cpp \
    Visual/dialogotiempos.cpp \
    dialogosimulacion.cpp \
    lote.cpp \
    proceso.cpp

HEADERS  += mainwindow.h \
    Modelo/genera_procesos.h \
    Modelo/simulasistemaoperativo.h \
    Visual/clock.h \
    Visual/dialogotiempos.h \
    dialogosimulacion.h \
    lote.h \
    proceso.h

FORMS    += mainwindow.ui
