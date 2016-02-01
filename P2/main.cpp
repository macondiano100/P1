#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <memory>
#include <Modelo/genera_procesos.h>
#include <iostream>
#include <sstream>
#include<proceso.h>

int main(int argc, char *argv[])
{QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
