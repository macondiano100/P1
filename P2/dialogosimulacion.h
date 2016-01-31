#ifndef DIALOGOSIMULACION_H
#define DIALOGOSIMULACION_H

#include <QDialog>
#include <list>
#include <memory>
#include <QStringListModel>
#include <unordered_map>
#include "lote.h"
namespace Ui {
class DialogoSimulacion;
}

class DialogoSimulacion : public QDialog
{
    Q_OBJECT
    std::map <Operador,QString> *opcionesOperadores;
    using Lote_shrdptr=std::shared_ptr<Lote>;
    std::list<Lote_shrdptr> lotesPendientes;
    std::list<std::shared_ptr<Lote>> lotesTerminados;
    Lote::Proceso_ptr proceso_en_ejecucion;
    Lote_shrdptr lote_en_ejecucion;
    void keyPressEvent(QKeyEvent *event);
public:
    explicit DialogoSimulacion(std::list<Lote_shrdptr> &lotes,QWidget *parent = 0 );
    ~DialogoSimulacion();

private:

    Ui::DialogoSimulacion *ui;
    QStringListModel* modeloListaLoteActual;
    QStringListModel* modeloListaProcesoTerminados;
    void updateLabelLotesRestantes();
    void updateListaProcesosTerminados();
    void updateListaLoteActual();
    void updateLabelProcesoActual(int tiempoTranscurrido=0);
    unsigned tiempoProcesoActual;
    bool finishedSimulation;
 private slots:
    void changeView(unsigned currTime);
};

#endif // DIALOGOSIMULACION_H
