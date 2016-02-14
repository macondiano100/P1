#ifndef DIALOGOTIEMPOS_H
#define DIALOGOTIEMPOS_H

#include <QDialog>
#include <QStandardItemModel>
#include "Modelo/simulasistemaoperativo.h"
namespace Ui {
class DialogoTiempos;
}

class DialogoTiempos : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoTiempos(SimulaSistemaOperativo::Registro_Tiempos &&tiempos, QWidget *parent = 0);
    ~DialogoTiempos();

private:
    Ui::DialogoTiempos *ui;
     QStandardItemModel *modelo;
};

#endif // DIALOGOTIEMPOS_H
