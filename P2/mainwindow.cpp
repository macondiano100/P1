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
    GeneradorProcesos g(ui->spinBoxNumeroProcesos->value());
    int maxPorLote=4;
    int cuentaProcesos=maxPorLote;
    lotes.clear();
    while(!g.finished()){
        if(cuentaProcesos>=maxPorLote)
        {
            lotes.push_back(std::make_shared<Lote>(maxPorLote));
            cuentaProcesos=0;
        }
        lotes.back()->push(g.next());
        cuentaProcesos++;
    }
    dialogoSimulacion=new DialogoSimulacion(lotes,this);
    dialogoSimulacion->exec();
    delete dialogoSimulacion;
    dialogoSimulacion=nullptr;
}
