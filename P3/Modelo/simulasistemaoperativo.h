#ifndef SIMULASISTEMAOPERATIVO_H
#define SIMULASISTEMAOPERATIVO_H

#include <QObject>
#include <list>
#include <memory>
#include <proceso.h>
#include <unordered_map>
class Memoria: public QObject
{
    Q_OBJECT
    using ListaProcesos=std::list<std::unique_ptr<Proceso>>;
    using IteraProcesos=ListaProcesos::iterator;
    ListaProcesos listos;
    std::unique_ptr<Proceso> procesoEjecucion;
    ListaProcesos bloqueados;
    size_t curr_size;
    const size_t MAX_SIZE;
public:
    void bloqueaEjecucion();
    void ejecutaSiguiente();
    void agregaProceso(std::unique_ptr<Proceso> &&proceso);
    IteraProcesos beginProcesosListos();
    IteraProcesos endProcesosListos();
    IteraProcesos beginProcesosBloqueados();
    IteraProcesos endProcesosBloqueados();
    std::unique_ptr<Proceso> &getProcesoEjecucion();
    bool llena();
    void desbloquear(IteraProcesos pos);
    Memoria(size_t MAX_SIZE=0);
};



class SimulaSistemaOperativo : public QObject
{


    Q_OBJECT
    struct infoTiempoProceso
    {
        uint segundoLlegada;
        uint segundoFinalizacion;
        uint segundoRespuesta;
        uint tiempoServicio;
        uint tiempoEspera;
    };
    std::unordered_map<int,infoTiempoProceso> tiempos;
    int segundoActual;
    std::list<std::unique_ptr<Proceso>> creados;
    std::list<std::unique_ptr<Proceso>> terminados;
public:
    Memoria memoria;
    explicit SimulaSistemaOperativo(QObject *parent = 0);
    ~SimulaSistemaOperativo();
    template<typename Iter> void agregaProcesos
    (Iter primero, Iter fin);
public slots:
    void clock();
signals:
};
#include <QDebug>
template<typename Iter> void SimulaSistemaOperativo::agregaProcesos
(Iter primero, Iter fin)
{
    while(primero!=fin)
    {
        tiempos[(*primero)->getId()]={segundoActual,-1,-1,-1,(*primero)->getMaxTiempo()};
        creados.push_back(move(*primero));
        primero++;
    }
}

#endif // SIMULASISTEMAOPERATIVO_H
