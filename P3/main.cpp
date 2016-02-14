#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <memory>
#include <Modelo/genera_procesos.h>
#include <iostream>
#include <sstream>
#include <proceso.h>
#include <list>
#include <QDebug>
#include <dialogosimulacion.h>
#include <Modelo/simulasistemaoperativo.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow application;

    SimulaSistemaOperativo simulador;
    std::list<std::unique_ptr<Proceso>> procesos;
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(1,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(2,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(3,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(4,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(5,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(6,"2","2",Operador::DIVISION,1)));
    procesos.push_back(std::unique_ptr<Proceso>(new Proceso(7,"2","2",Operador::DIVISION,1)));
    DialogoSimulacion d(procesos);
    d.exec();
    return application.e;
}
*/
