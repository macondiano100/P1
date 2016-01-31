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
    std::list<Lote_shrdptr> lotes;
    DialogoSimulacion* dialogoSimulacion;
    void notificaError(QString razon);
private slots:
    void nProcesosELegido();
    void accionBotonIniciarSimulacion();
};

#endif // MAINWINDOW_H
