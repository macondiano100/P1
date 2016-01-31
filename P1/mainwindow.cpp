#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMap>
#include <QMessageBox>
#include <unordered_map>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialogoSimulacion(nullptr)
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
    if(dialogoSimulacion!=nullptr)delete dialogoSimulacion;
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
    if(!validaCampos()) return;
    if(tamanioLoteActual==0)
    {
        loteActual.reset(new Lote(LOTE_SIZE));
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
        if(tamanioLoteActual>=LOTE_SIZE)
        {
            tamanioLoteActual=0;
            lotes.push_back(loteActual);
        }
    }

}

bool MainWindow::validaCampos()
{
    Operador operador=opcionesOperadores->at(ui->comboOperacion->currentText());
    bool camposValidos=true;
    QString razon;
    if(operador==Operador::DIVISION||operador==Operador::RESTO)
    {
        if(ui->spinOperador2->text().toDouble()==0){
            camposValidos=false;
            razon=tr("No se puede dividir entre cero.");
        }
    }
    else if(operador==Operador::RAIZ)
    {
        if(ui->spinOperador1->text().toDouble()<0){
            camposValidos=false;
            razon=tr("Las raíces de números negativos no existen.");
        }
    }
    int id=ui->spinId->text().toInt();
    if(loteActual!=nullptr)
    {for(auto p:*loteActual)
        {if(p->getId()==id){
                camposValidos=false;
                razon=tr("ID ya existe");
                break;}}}
    for(auto l:lotes){
        for(auto p:*l){
            if(p->getId()==id){
                camposValidos=false;
                razon=tr("ID ya existe");
                break;}}}
    if(!camposValidos)notificaError(razon);
    return camposValidos;
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
