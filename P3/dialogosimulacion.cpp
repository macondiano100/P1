#include "dialogosimulacion.h"
#include "ui_dialogosimulacion.h"
#include <QList>
#include <memory>
#include <QKeyEvent>
#include <iostream>
#include <QDebug>
void DialogoSimulacion::tomaSiguienteProceso()
{
    if(lote_en_ejecucion->empty())
    {
        if(lotesPendientes.empty())
        {
            finishedSimulation=true;
            proceso_en_ejecucion.reset();
            updateLabelProcesoActual();
            return;
        }
        else
        {
            lote_en_ejecucion=lotesPendientes.front();
            lotesPendientes.pop_front();
            lotesTerminados.push_back(std::make_shared<Lote>(LOTE_SIZE));
            updateLabelLotesRestantes();
        }
    }
    proceso_en_ejecucion=lote_en_ejecucion->pop();
    updateLabelProcesoActual();
    updateListaLoteActual();
}

void DialogoSimulacion::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_I:
        tomaSiguienteProceso();
        break;
    case Qt::Key_B:
        lote_en_ejecucion->push(proceso_en_ejecucion);
        std::cout<<"B"<<std::endl;
        tomaSiguienteProceso();
        break;
    case Qt::Key_P:
        ui->clock->pause();
        break;
    case Qt::Key_C:
        ui->clock->resume();
        break;
    case Qt::Key_E:
        proceso_en_ejecucion->setOcurrioError();
        lotesTerminados.back()->push(proceso_en_ejecucion);
        tomaSiguienteProceso();
        updateListaProcesosTerminados();
        break;
    default:
        break;
    }
}

DialogoSimulacion::DialogoSimulacion
(std::list<Lote_shrdptr> &lotes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoSimulacion),
    finishedSimulation(false)
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
    ui->clock->start(1000);
    lotesPendientes=lotes;
    lote_en_ejecucion=lotesPendientes.front();
    lotesPendientes.pop_front();
    proceso_en_ejecucion=lote_en_ejecucion->pop();
    lotesTerminados.push_back(std::make_shared<Lote>(LOTE_SIZE));
    updateLabelProcesoActual();
    updateLabelLotesRestantes();
    modeloListaLoteActual=new QStringListModel(this);
    modeloListaProcesoTerminados=new QStringListModel(this);
    ui->listaLoteActual->setModel(modeloListaLoteActual);
    ui->listaLoteActual->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listaProcesosTerminados->setModel(modeloListaProcesoTerminados);
    ui->listaProcesosTerminados->setEditTriggers(QAbstractItemView::NoEditTriggers);
    updateListaLoteActual();
    connect(ui->clock,SIGNAL(updated(uint)),this,SLOT(timeAction(uint)));
}

DialogoSimulacion::~DialogoSimulacion()
{
    delete ui;
    delete modeloListaLoteActual;
    delete modeloListaProcesoTerminados;
}



void DialogoSimulacion::updateLabelLotesRestantes()
{
    ui->labelLotesRestantes->setText(QString::number(lotesPendientes.size()));
}

void DialogoSimulacion::updateListaLoteActual()
{
    QList<QString> items;
    for(auto p:*lote_en_ejecucion)
        items<<p->getNombreProgramador()+
               tr("\nT.M.E: ")+QString::number(p->getMaxTiempo())+
               tr("\nTiempo Restante: ")+QString::number(p->getTiempoEjecucionRestante());
    modeloListaLoteActual->setStringList(items);
}
void DialogoSimulacion::updateListaProcesosTerminados()
{
    QList<QString> items;
    QString s;
    int i=1;
    for(auto l:lotesTerminados)
    {
        items<<tr("Lote: ")+QString::number(i++)+
               "\n----------------------------------------------";
        for(auto p:*l)
        {
            s+=tr("Id: ")+
                   QString::number(p->getId())+
                   tr("\n");
            if(p->getOperador()==Operador::RAIZ)
                s+="\u221A"+p->getOperando1();
            else s+=p->getOperando1()+opcionesOperadores->at(p->getOperador())+
                   p->getOperando2();
            s+=tr("=")+p->getResultado()+tr("\n");
            items<<s;
            s.clear();
        }
    }
    modeloListaProcesoTerminados->setStringList(items);
}
void DialogoSimulacion::updateLabelProcesoActual()
{
    if(!finishedSimulation) ui->label_proceso_actual->setText(
                tr("Programador:")+proceso_en_ejecucion->getNombreProgramador()+"\n"+
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
    else ui->label_proceso_actual->setText("");
}
#include<QDebug>

void DialogoSimulacion::timeAction(unsigned currTime)
{
    if(!finishedSimulation)
    {
        qDebug()<<"Call me";
        proceso_en_ejecucion->avanzaEjecucion();
        updateLabelProcesoActual();
        if(proceso_en_ejecucion->terminado())
        {
            proceso_en_ejecucion->solve();
            lotesTerminados.back()->push(proceso_en_ejecucion);
            updateListaProcesosTerminados();
            std::cout<<"Llamada"<<std::endl;
            tomaSiguienteProceso();
        }
    }

}
