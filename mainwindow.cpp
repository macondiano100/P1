#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMap>
#include <unordered_map>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setHabilitacionCamposProceso(false);
    opcionesOperadores
            = new std::map<QString, Operador>;
    opcionesOperadores->insert({
                                   {tr("Suma"),Operador::SUMA},
                                   {tr("Resta"),Operador::RESTA},
                                   {tr("Multiplicación"),Operador::MULTIPLICACION},
                                   {tr("División"),Operador::DIVISION},
                                   {tr("Resto"),Operador::RESTO},
                                   {tr("Raíz Cuadrada"),Operador::RAIZ}
                                });
    tamanioLoteActual=0;
    for(auto pair:*opcionesOperadores)
        ui->comboOperacion->addItem(pair.first);

}

MainWindow::~MainWindow()
{
    delete opcionesOperadores;
    delete ui;
}

void MainWindow::setHabilitacionCamposProceso(bool enabled)
{
    ui->campoNombreProgramador->setEnabled(enabled);
    ui->comboOperacion->setEnabled(enabled);
    ui->spinOperador1->setEnabled(enabled);
    ui->spinOperador2->setEnabled(enabled);
    ui->comboOperacion->setEnabled(enabled);
    ui->spinMaxTime->setEnabled(enabled);
    ui->spinId->setEnabled(enabled);
    ui->botonSIguienteProceso->setEnabled(enabled);
}

void MainWindow::updateCuentaGroupBoxProcesos()
{
    QString s="Información del Proceso Número "+
            QString::number(nProcesosIntroducidos +1);
    ui->groupInfoProceso->setTitle(s);
}
void MainWindow::nProcesosELegido()
{
    int nProcesos;
    nProcesos=ui->spinBoxNumeroProcesos->value();
    if(nProcesos>0)
    {
        ui->botonNumeroProcesos->setEnabled(false);
        ui->spinBoxNumeroProcesos->setEnabled(false);
        nProcesosIntroducir=nProcesos;
        nProcesosIntroducidos=0;
        setHabilitacionCamposProceso(true);
        updateCuentaGroupBoxProcesos();
    }
}

void MainWindow::accionBotonSiguienteProceso()
{
    if(tamanioLoteActual==0)
    {
        loteActual.reset(new Lote(4));
    }
    Operador op=opcionesOperadores->at(ui->comboOperacion->currentText());
    Lote::Proceso_ptr proceso(new Proceso(ui->campoNombreProgramador->text(),
                                          ui->spinId->text().toInt(),
                                          ui->spinOperador1->text(),
                                          ui->spinOperador2->text(),
                                          op,
                                          ui->spinMaxTime->text().toInt()
                                         ));
    loteActual->push(proceso);
    tamanioLoteActual++;
    nProcesosIntroducidos++;
    if(nProcesosIntroducidos>=nProcesosIntroducir)
    {
        lotes.push_back(loteActual);
        setHabilitacionCamposProceso(false);
        ui->botonSimular->setEnabled(true);
    }
    else{
        updateCuentaGroupBoxProcesos();
        if(tamanioLoteActual>=MAX_PROCESOS_POR_LOTE)
        {
            tamanioLoteActual=0;
            lotes.push_back(loteActual);
        }
    }

}
