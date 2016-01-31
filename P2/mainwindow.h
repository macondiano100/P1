#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include <memory>
#include "proceso.h"
#include "dialogosimulacion.h"
#include "lote.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    using Lote_shrdptr=std::shared_ptr<Lote>;
    Ui::MainWindow *ui;
    unsigned nProcesosIntroducir;
    unsigned nProcesosIntroducidos;
    unsigned tamanioLoteActual;
    Lote_shrdptr loteActual;
    void setHabilitacionCamposProceso(bool enabled);
    void updateCuentaGroupBoxProcesos();
    std::map <QString,Operador> *opcionesOperadores;
    std::list<Lote_shrdptr> lotes;
    DialogoSimulacion* dialogoSimulacion;
    bool validaCampos();
    void notificaError(QString razon);
private slots:
    void nProcesosELegido();
    void accionBotonSiguienteProceso();
    void accionBotonIniciarSimulacion();
};

#endif // MAINWINDOW_H
