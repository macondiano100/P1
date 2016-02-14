#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMap>
#include <QMessageBox>
#include <unordered_map>
#include <QDebug>
#include <limits>
#include <Modelo/genera_procesos.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialogoSimulacion(nullptr)
{
    ui->setupUi(this);
    ui->spinBoxNumeroProcesos->setMaximum(std::numeric_limits<int>::max());
}

MainWindow::~MainWindow()
{
    if(dialogoSimulacion!=nullptr)delete dialogoSimulacion;
    delete ui;
}


void MainWindow::accionBotonIniciarSimulacion()
{
    GeneradorProcesos g(ui->spinBoxNumeroProcesos->value());
    std::list<std::unique_ptr<Proceso>> procesos;
    while(!g.finished()){
        procesos.push_back(std::move(g.next()));
    }
    dialogoSimulacion=new DialogoSimulacion(procesos,this);
    dialogoSimulacion->exec();
    delete dialogoSimulacion;
    dialogoSimulacion=nullptr;
}
