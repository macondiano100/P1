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
    IteraProcesos beginProcesosListos();
    IteraProcesos endProcesosListos();
    IteraProcesos beginProcesosBloqueados();
    IteraProcesos endProcesosBloqueados();
    std::unique_ptr<Proceso> &getProcesoEjecucion();
    bool llena();
    void desbloquear(IteraProcesos pos);
    Memoria(size_t MAX_SIZE=0);
    std::unique_ptr<Proceso> resuelveProcesoEnEjecucion();
    void bloqueaEjecucion(unsigned t);
    std::unique_ptr<Proceso> errorEjecucion();
    void agregaProceso(std::unique_ptr<Proceso> &&proceso);
    size_t sizeProcesosListos();
};



class SimulaSistemaOperativo : public QObject
{


    Q_OBJECT

    using ListaProcesos=std::list<std::unique_ptr<Proceso>>;
    using IteraProcesos=ListaProcesos::iterator;
public:
    struct infoTiempoProceso
    {
        static constexpr unsigned int npos=-1;
        uint segundoLlegada;
        uint segundoFinalizacion;
        uint segundoInicio;
        uint tiempoServicio;
    };
    using Registro_Tiempos=std::unordered_map<int,infoTiempoProceso>;
private:
    Registro_Tiempos tiempos;
    int segundoActual;
    std::list<std::unique_ptr<Proceso>> creados;
    std::list<std::unique_ptr<Proceso>> terminados;
    void actualizaProcesoEnEjecucion();
    void insertaProcesosAMemoria();
    void actualizaProcesosBloqueados();
    void actualizaProcesosListos();
    bool finalizado;
public:
    Memoria memoria;
    explicit SimulaSistemaOperativo(QObject *parent = 0);
    ~SimulaSistemaOperativo();
    template<typename Iter> void agregaProcesos
    (Iter primero, Iter fin);
    void agregaProceso(std::unique_ptr<Proceso> &&proceso);
    IteraProcesos beginProcesosListos();
    IteraProcesos endProcesosListos();
    IteraProcesos beginProcesosTerminados();
    IteraProcesos endProcesosTerminados();
    IteraProcesos beginProcesosBloqueados();
    IteraProcesos endProcesosBloqueados();
    void bloqueaProceso(unsigned t);
    void forzarError();
    bool simulacionTerminada();
    Registro_Tiempos dameRegitroTiempos();
    std::unique_ptr<Proceso> &getProcesoEnEjecucion();
    size_t sizeProcesosCreados();
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
        tiempos[(*primero)->getId()]={infoTiempoProceso::npos,infoTiempoProceso::npos,
                infoTiempoProceso::npos,(*primero)->getMaxTiempo()};
        creados.push_back(move(*primero));
        primero++;
    }
    insertaProcesosAMemoria();
    actualizaProcesoEnEjecucion();

}

#endif // SIMULASISTEMAOPERATIVO_H
