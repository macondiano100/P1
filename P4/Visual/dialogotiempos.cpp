#include "dialogotiempos.h"
#include "ui_dialogotiempos.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QKeyEvent>
#include "proceso.h"


DialogoTiempos::DialogoTiempos
(SimulaSistemaOperativo &sistemaOperativo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoTiempos)
{
    ui->setupUi(this);
    ui->tableViewTiempos->setWordWrap(true);
    modelo=new QStandardItemModel(this);
    opcionesOperadores=new std::map <Operador,QString>;
    nombresEstados=new std::map <ESTADOS_PCB,QString>;
    opcionesOperadores->insert({
                                   {Operador::SUMA,tr("+")},
                                   {Operador::RESTA,tr("-")},
                                   {Operador::MULTIPLICACION,tr("*")},
                                   {Operador::DIVISION,tr("/")},
                                   {Operador::RESTO,tr("%")},
                                   {Operador::RAIZ,tr("sqrt ")}
                                });
    nombresEstados->insert({
                                   {EJECUCION,tr("Ejecución")},
                                   {LISTO,tr("Listo")},
                                   {CREADO,tr("Creado")},
                                   {TERMINADO,tr("Terminado")}
                                });
    infoProcesos=sistemaOperativo.dameRegitroTiempos();
    modelo->setHorizontalHeaderItem(COL_ID,new QStandardItem(tr("Id")));
    modelo->setHorizontalHeaderItem(COL_ESTADO,new QStandardItem(tr("Estado")));
    modelo->setHorizontalHeaderItem(COL_OPERACION,new QStandardItem(tr("Operación")));
    modelo->setHorizontalHeaderItem(COL_LLEGADA,new QStandardItem(tr("Llegada")));
    modelo->setHorizontalHeaderItem(COL_FINALIZACION,new QStandardItem(tr("Finalización")));
    modelo->setHorizontalHeaderItem(COL_RETORNO,new QStandardItem(tr("Tiempo \nde retorno")));
    modelo->setHorizontalHeaderItem(COL_ESPERA,new QStandardItem(tr("Tiempo \nde espera")));
    modelo->setHorizontalHeaderItem(COL_SERVICIO,new QStandardItem(tr("Tiempo \nde servicio")));
    modelo->setHorizontalHeaderItem(COL_RESTANTE,new QStandardItem(tr("Tiempo \nrestante")));
    modelo->setHorizontalHeaderItem(COL_RESPUESTA,new QStandardItem(tr("Tiempo \nde Respuesta")));
    populateTable(sistemaOperativo);
}

DialogoTiempos::~DialogoTiempos()
{
    delete opcionesOperadores;
    delete nombresEstados;
    delete ui;
    delete modelo;
}

void DialogoTiempos::populateTable(SimulaSistemaOperativo &sistemaOperativo)
{
    using IteraProcesos=SimulaSistemaOperativo::IteraProcesos;
    ReferenciaProceso procesoEjecutandose=sistemaOperativo.getProcesoEnEjecucion();
    int rowActual=0;
    int segundoActual=sistemaOperativo.getSegundoActual();
    if(procesoEjecutandose!=nullptr)
    {
       populateRow(rowActual++,segundoActual,procesoEjecutandose,EJECUCION);
    }
   IteraProcesos beginListos=sistemaOperativo.beginProcesosListos(),
            endListos=sistemaOperativo.endProcesosListos();
    while(beginListos!=endListos){
        populateRow(rowActual++,segundoActual,*beginListos,LISTO);
        beginListos++;
    }
    IteraProcesos beginTerminados=sistemaOperativo.beginProcesosTerminados(),
            endTerminados=sistemaOperativo.endProcesosTerminados();
    while(beginTerminados!=endTerminados){
        populateRow(rowActual++,segundoActual,*beginTerminados,TERMINADO);
        beginTerminados++;
    }
    modelo->sort(COL_ID);
    ui->tableViewTiempos->setModel(modelo);
}
void DialogoTiempos::populateRow(int rowActual,int segundoActual,
                                 ReferenciaProceso proceso,ESTADOS_PCB estado)
{
     QStandardItem* itemId=new QStandardItem();
     itemId->setData(proceso->getId(),0);
     modelo->setItem(rowActual,COL_ID,itemId);
     modelo->setItem(rowActual,COL_ESTADO,new QStandardItem((*nombresEstados)[estado]));
     modelo->setItem(rowActual,COL_OPERACION,new QStandardItem(
                         dameCadenaOperacionProceso(proceso)
                         ));
     if(estado!=CREADO)
     {
         SimulaSistemaOperativo::infoTiempoProceso info=infoProcesos[proceso->getId()];
         modelo->setItem(rowActual,COL_LLEGADA,new QStandardItem(
                             QString::number(info.segundoLlegada)
                         ));
         if(estado==TERMINADO)
         {
             int tiempoRetorno=info.segundoFinalizacion-info.segundoLlegada;
             modelo->setItem(rowActual,COL_FINALIZACION,new QStandardItem(
                                 QString::number(info.segundoFinalizacion)));
             modelo->setItem(rowActual,COL_RETORNO,
                             new QStandardItem(QString::number(tiempoRetorno)));
             modelo->setItem(rowActual,COL_ESPERA, new QStandardItem(QString::number(
                                                                         tiempoRetorno-
                                                                         info.tiempoServicio)));
         }
         else{
             int tiempoEspera=
                     (segundoActual-info.segundoLlegada)-
                     (proceso->getMaxTiempo()-proceso->getTiempoEjecucionRestante());
             modelo->setItem(rowActual,COL_ESPERA, new QStandardItem(QString::number(
                                                                       tiempoEspera)));
         }
         modelo->setItem(rowActual,COL_SERVICIO, new QStandardItem(QString::number(
                                                                   info.tiempoServicio)));
         modelo->setItem(rowActual,COL_RESTANTE,new QStandardItem(QString::number(
                                                                   proceso->getTiempoEjecucionRestante()
                                                                   )));
         if(info.segundoInicio!=SimulaSistemaOperativo::infoTiempoProceso::npos)
         {
             modelo->setItem(rowActual,COL_RESPUESTA,
                             new QStandardItem(QString::number(info.segundoInicio-
                                                           info.segundoLlegada)));
         }
     }
}

QString DialogoTiempos::dameCadenaOperacionProceso(ReferenciaProceso p)
{
    QString s;
    if((p)->getOperador()==Operador::RAIZ)
        s+="\u221A"+(p)->getOperando1();
    else s+=(p)->getOperando1()+opcionesOperadores->at((p)->getOperador())+
           (p)->getOperando2();
    if(p->estaResuelto())s+=tr("=")+(p)->getResultado()+tr("\n");
    return s;
}

void DialogoTiempos::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_C) close();
}
