#include "dialogotiempos.h"
#include "ui_dialogotiempos.h"
#include <QStandardItemModel>
DialogoTiempos::DialogoTiempos
(SimulaSistemaOperativo::Registro_Tiempos &&tiempos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoTiempos)
{
    ui->setupUi(this);
    modelo=new QStandardItemModel(tiempos.size(),6,this);
    modelo->setHorizontalHeaderItem(0,new QStandardItem(tr("Tiempo de llegada")));
    modelo->setHorizontalHeaderItem(1,new QStandardItem(tr("Tiempo de finalización")));
    modelo->setHorizontalHeaderItem(2,new QStandardItem(tr("Tiempo de retorno")));
    modelo->setHorizontalHeaderItem(3,new QStandardItem(tr("Tiempo de respuesta")));
    modelo->setHorizontalHeaderItem(4,new QStandardItem(tr("Tiempo de espera")));
    modelo->setHorizontalHeaderItem(5,new QStandardItem(tr("Tiempo de servicio")));
    int i=tiempos.size()-1;
    int tiempoRetorno;
    for(auto item: tiempos)
    {
        modelo->setVerticalHeaderItem
                (i,new QStandardItem("Id "+QString::number(item.first)));
        modelo->setItem(i,0,new QStandardItem(QString::number(item.second.segundoLlegada)
                                              ));
        modelo->setItem(i,1,
                        new QStandardItem(QString::number(item.second.segundoFinalizacion))
                        );
        tiempoRetorno=item.second.segundoFinalizacion-item.second.segundoLlegada;
        modelo->setItem(i,2,
                        new QStandardItem(QString::number(tiempoRetorno))
                        );
        modelo->setItem(i,3,
                        new QStandardItem(QString::number(item.second.segundoInicio-
                                        item.second.segundoLlegada)));
        modelo->setItem(i,4,new QStandardItem(QString::number(tiempoRetorno-
                                            item.second.tiempoServicio)));
        modelo->setItem(i,5,new QStandardItem(QString::number(item.second.tiempoServicio)));
        i--;
    }
    ui->tableViewTiempos->setModel(modelo);
}

DialogoTiempos::~DialogoTiempos()
{
    delete ui;
    delete modelo;
}
