#ifndef DIALOGOSIMULACION_H
#define DIALOGOSIMULACION_H

#include <QDialog>
#include <list>
#include <memory>
#include <QStringListModel>
#include <unordered_map>
#include "modelo/simulasistemaoperativo.h"
namespace Ui {
class DialogoSimulacion;
}

class DialogoSimulacion : public QDialog
{
    Q_OBJECT
    std::map <Operador,QString> *opcionesOperadores;
    void keyPressEvent(QKeyEvent *event);
    static constexpr int TIEMPO_BLOQUEO=8;
public:
    explicit DialogoSimulacion(std::list<std::unique_ptr<Proceso>> &procesos,QWidget *parent = 0);
    ~DialogoSimulacion();
    SimulaSistemaOperativo sistemaOperativo;
private:

    QStringListModel* modeloListaLoteActual;
    QStringListModel* modeloListaProcesoTerminados;
    QStringListModel* modeloListaProcesoBloqueados;
    bool paused;
    Ui::DialogoSimulacion *ui;
    void updateAllView();
    void updateLabelLotesRestantes();
    void updateListaProcesosTerminados();
    void updateListaProcesosBloqueados();
    void updateListaProcesosListos();
    void updateLabelProcesoActual();
 private slots:
    void timeAction();
};

#endif // DIALOGOSIMULACION_H
