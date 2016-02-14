
#include <QList>
#include <memory>
#include <QKeyEvent>
#include <iostream>
#include <QDebug>
#include "dialogosimulacion.h"
#include "ui_dialogosimulacion.h"
#include "Modelo/genera_procesos.h"
#include "Visual/dialogotiempos.h"
void DialogoSimulacion::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_I:
        if(!paused){
            sistemaOperativo.bloqueaProceso(TIEMPO_BLOQUEO);
        }
        break;
    case Qt::Key_P:
        paused=true;
        ui->clock->pause();
        break;
    case Qt::Key_N:

        //if(!paused)
        {
            GeneradorProcesos generador(1);
            sistemaOperativo.agregaProceso(generador.next());
            updateLabelProcesosCreados();
            updateListaProcesosListos();
      }
        break;
    case Qt::Key_C:
        paused=false;
        ui->clock->resume();
        break;
    case Qt::Key_E:
        if(!paused)
        {
            sistemaOperativo.forzarError();
            updateListaProcesosTerminados();
            updateLabelProcesoActual();
        }
        break;
    default:
        break;
    }
}



DialogoSimulacion::DialogoSimulacion
(std::list<std::unique_ptr<Proceso> > &procesos, QWidget *parent):
    QDialog(parent),sistemaOperativo(),
    paused(false),
    ui(new Ui::DialogoSimulacion)
{
    ui->setupUi(this);
    opcionesOperadores
            = new std::map<Operador, QString>;
    opcionesOperadores->insert({
                                   {Operador::SUMA,tr("+")},
                                   {Operador::RESTA,tr("-")},
                                   {Operador::MULTIPLICACION,tr("*")},
                                   {Operador::DIVISION,tr("/")},
                                   {Operador::RESTO,tr("%")},
                                   {Operador::RAIZ,tr("sqrt ")}
                                });
    sistemaOperativo.agregaProcesos(procesos.begin(),procesos.end());
    ui->clock->start(1000);
    modeloListaLoteActual=new QStringListModel(this);
    modeloListaProcesoTerminados=new QStringListModel(this);
    modeloListaProcesoBloqueados=new QStringListModel(this);
    ui->listaLoteActual->setModel(modeloListaLoteActual);
    ui->listaLoteActual->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listaProcesosTerminados->setModel(modeloListaProcesoTerminados);
    ui->listaProcesosTerminados->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listaProcesosBloqueados->setModel(modeloListaProcesoBloqueados);
    ui->listaProcesosBloqueados->setEditTriggers(QAbstractItemView::NoEditTriggers);
    updateListaProcesosListos();
    updateLabelProcesosCreados();
    updateLabelProcesoActual();
    connect(ui->clock,SIGNAL(updated()),this,SLOT(timeAction()));
}

DialogoSimulacion::~DialogoSimulacion()
{
    delete ui;
    delete modeloListaLoteActual;
    delete modeloListaProcesoTerminados;
}



void DialogoSimulacion::updateLabelProcesosCreados()
{
    ui->labelNuevos->setText(QString::number(sistemaOperativo.sizeProcesosCreados()));
}

void DialogoSimulacion::updateListaProcesosListos()
{
    QList<QString> items;
    auto p=sistemaOperativo.beginProcesosListos(),
            endListos=sistemaOperativo.endProcesosListos();
    while(p!=endListos)
    {
        items<<tr("Id: ")+QString::number((*p)->getId())+
               tr("\nT.M.E: ")+QString::number((*p)->getMaxTiempo())+
               tr("\nTiempo Restante: ")+QString::number((*p)->getTiempoEjecucionRestante());
        p++;
    }
    modeloListaLoteActual->setStringList(items);
}
void DialogoSimulacion::updateListaProcesosTerminados()
{
    QList<QString> items;
    QString s;
    auto p=sistemaOperativo.beginProcesosTerminados(),
            end=sistemaOperativo.endProcesosTerminados();
    while(p!=end)
    {
        s+=tr("Id: ")+
               QString::number((*p)->getId())+
               tr("\n");
        if((*p)->getOperador()==Operador::RAIZ)
            s+="\u221A"+(*p)->getOperando1();
        else s+=(*p)->getOperando1()+opcionesOperadores->at((*p)->getOperador())+
               (*p)->getOperando2();
        s+=tr("=")+(*p)->getResultado()+tr("\n");
        items<<s;
        s.clear();
        p++;
    }
    modeloListaProcesoTerminados->setStringList(items);
}

void DialogoSimulacion::updateListaProcesosBloqueados()
{
    QList<QString> items;
    QString s;
    auto p=sistemaOperativo.beginProcesosBloqueados(),
            end=sistemaOperativo.endProcesosBloqueados();
    while(p!=end)
    {
        s+=tr("Id: ")+
               QString::number((*p)->getId())+
               tr("\n")+
                tr("Bloqueado por: ")+QString::number(
                    TIEMPO_BLOQUEO-(*p)->getTiempoBloqueoRestante()
                    )+
                tr(" segundos");
        items<<s;
        s.clear();
        p++;
    }
    modeloListaProcesoBloqueados->setStringList(items);
}
void DialogoSimulacion::updateLabelProcesoActual()
{
    auto& proceso_en_ejecucion=sistemaOperativo.getProcesoEnEjecucion();
    if(!(proceso_en_ejecucion==nullptr))
    ui->label_proceso_actual->setText(
                tr("Operación: ")+
                opcionesOperadores->at(proceso_en_ejecucion->getOperador())+" "+
                proceso_en_ejecucion->getOperando1()+","+
                proceso_en_ejecucion->getOperando2()+"\n"+
                tr("T.M.E: ")+QString::number(proceso_en_ejecucion->getMaxTiempo())+"\n"+
                tr("Id: ")+QString::number(proceso_en_ejecucion->getId())+"\n"+
                tr("Tiempo Transcurrido: ")+QString::number(
                    proceso_en_ejecucion->getMaxTiempo()-
                    proceso_en_ejecucion->getTiempoEjecucionRestante())+"\n"+
                tr("Tiempo Restante: ")+QString::number(
                    proceso_en_ejecucion->getTiempoEjecucionRestante()
                    )
                );
    else ui->label_proceso_actual->setText("");/**/
}
#include<QDebug>

void DialogoSimulacion::timeAction()
{
    if(sistemaOperativo.simulacionTerminada())
    {
        ui->clock->pause();
        DialogoTiempos d(sistemaOperativo.dameRegitroTiempos());
        d.exec();
        close();
    }
    else
    {
        sistemaOperativo.clock();
        updateLabelProcesoActual();
        updateListaProcesosListos();
        updateListaProcesosTerminados();
        updateListaProcesosBloqueados();
        updateLabelProcesosCreados();
    }
}
