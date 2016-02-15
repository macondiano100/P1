#ifndef DIALOGOTIEMPOS_H
#define DIALOGOTIEMPOS_H

#include <QDialog>
#include <QStandardItemModel>
#include "Modelo/simulasistemaoperativo.h"
namespace Ui {
class DialogoTiempos;
}
enum COLUMNAS
{
    COL_ID=0,COL_ESTADO,COL_OPERACION,COL_LLEGADA,COL_FINALIZACION,COL_RETORNO,
    COL_ESPERA,COL_SERVICIO,COL_RESTANTE,COL_RESPUESTA
};
enum ESTADOS_PCB
{
    EJECUCION,CREADO,TERMINADO,LISTO
};
class DialogoTiempos : public QDialog
{
    Q_OBJECT

public:
    using ReferenciaProceso=std::unique_ptr<Proceso>&;
    explicit DialogoTiempos(SimulaSistemaOperativo &sistemaOperativo, QWidget *parent = 0);
    ~DialogoTiempos();

private:
    SimulaSistemaOperativo::Registro_Tiempos infoProcesos;
    QStandardItemModel *modelo;
    std::map <Operador,QString> *opcionesOperadores;
    std::map <ESTADOS_PCB,QString> *nombresEstados;
    Ui::DialogoTiempos *ui;
    void populateTable(SimulaSistemaOperativo &sistemaOperativo);
    QString dameCadenaOperacionProceso(ReferenciaProceso p);
    void keyPressEvent(QKeyEvent* event) override;
    void populateRow(int rowActual, int segundoActual, ReferenciaProceso proceso, ESTADOS_PCB estado);
};

#endif // DIALOGOTIEMPOS_H
