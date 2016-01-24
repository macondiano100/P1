#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include <memory>
#include "proceso.h"
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
    static constexpr int MAX_PROCESOS_POR_LOTE=4;
    Ui::MainWindow *ui;
    unsigned nProcesosIntroducir;
    unsigned nProcesosIntroducidos;
    unsigned tamanioLoteActual;
    Lote_shrdptr loteActual;
    void setHabilitacionCamposProceso(bool enabled);
    void updateCuentaGroupBoxProcesos();
    std::map <QString,Operador> *opcionesOperadores;
    std::list<Lote_shrdptr> lotes;
private slots:
    void nProcesosELegido();
    void accionBotonSiguienteProceso();
};

#endif // MAINWINDOW_H
