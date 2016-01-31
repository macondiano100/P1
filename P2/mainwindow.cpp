#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMap>
#include <QMessageBox>
#include <unordered_map>
#include <QDebug>
#include <limits>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialogoSimulacion(nullptr)
{
    ui->setupUi(this);
    ui->spinBoxNumeroProcesos->setRange(std::numeric_limits<int>::min(),
                                        std::numeric_limits<int>::max());
}

MainWindow::~MainWindow()
{
    if(dialogoSimulacion!=nullptr)delete dialogoSimulacion;
    delete ui;
}




void MainWindow::nProcesosELegido()
{
    int nProcesos;
    nProcesos=ui->spinBoxNumeroProcesos->value();
    if(nProcesos>0)
    {
        ui->spinBoxNumeroProcesos->setEnabled(false);
    }
}
void MainWindow::notificaError(QString razon)
{
    QMessageBox msgBOx(this);
    msgBOx.setText(razon);
    msgBOx.exec();
}

void MainWindow::accionBotonIniciarSimulacion()
{
    dialogoSimulacion=new DialogoSimulacion(lotes,this);
    dialogoSimulacion->exec();
    delete dialogoSimulacion;
    dialogoSimulacion=nullptr;
}
