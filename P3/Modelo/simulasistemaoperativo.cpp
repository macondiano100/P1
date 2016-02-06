#include "simulasistemaoperativo.h"

SimulaSistemaOperativo::SimulaSistemaOperativo(QObject *parent) : QObject(parent),memoria(4)
{

}

SimulaSistemaOperativo::~SimulaSistemaOperativo()
{

}
#include <QDebug>
void SimulaSistemaOperativo::clock()
{
    auto& procesoEjecutandose=memoria.getProcesoEjecucion();
    segundoActual++;
    auto beginProcesosCreados=creados.begin(),endCreados=creados.end();
    while(!memoria.llena()&&beginProcesosCreados!=endCreados)
    {
        memoria.agregaProceso(move(*beginProcesosCreados));
        beginProcesosCreados=creados.erase(beginProcesosCreados);
    }
    if(procesoEjecutandose==nullptr){
        memoria.ejecutaSiguiente();
        auto& procesoEjecutandose=memoria.getProcesoEjecucion();
         if(tiempos[procesoEjecutandose->getId()].segundoRespuesta==(unsigned)-1);
           tiempos[procesoEjecutandose->getId()].segundoRespuesta=segundoActual;
    }
    procesoEjecutandose->avanzaEjecucion();
    if(procesoEjecutandose->terminado()){
        procesoEjecutandose->solve();
        qDebug()<<"Solved "<<procesoEjecutandose->getId();
        tiempos[procesoEjecutandose->getId()].segundoFinalizacion=segundoActual;
        terminados.push_back(move(procesoEjecutandose));
    }
    auto beginBloqueados=memoria.beginProcesosBloqueados();
    auto endBloqueados=memoria.endProcesosBloqueados();
    while(beginBloqueados!=endBloqueados)
    {
        (*beginBloqueados)->avanzaTiempoBloqueo();
        tiempos[(*beginBloqueados)->getId()].tiempoEspera++;
        if(!(*beginBloqueados)->bloqueado())memoria.desbloquear(beginBloqueados);
        beginBloqueados++;
    }

    auto beginListos=memoria.beginProcesosListos();
    auto endListos=memoria.endProcesosListos();
    while(beginListos!=endListos)
    {
        tiempos[(*beginListos)->getId()].tiempoEspera++;
        beginListos++;
    }
}



void Memoria::ejecutaSiguiente()
{
    if(!listos.empty())
    {
        procesoEjecucion=std::move(listos.front());
        listos.pop_front();
    }
}

void Memoria::bloqueaEjecucion()
{
    bloqueados.push_back(std::move(procesoEjecucion));
    ejecutaSiguiente();
}

void Memoria::agregaProceso(std::unique_ptr<Proceso> &&proceso)
{
    if(curr_size<MAX_SIZE)
    {
        listos.push_back(move(proceso));
        curr_size++;
    }
}

Memoria::IteraProcesos Memoria::beginProcesosListos()
{
    return listos.begin();
}

Memoria::IteraProcesos Memoria::endProcesosListos()
{
    return listos.end();
}

Memoria::IteraProcesos Memoria::beginProcesosBloqueados()
{
    return bloqueados.begin();
}

Memoria::IteraProcesos Memoria::endProcesosBloqueados()
{
    return bloqueados.end();
}

std::unique_ptr<Proceso>& Memoria::getProcesoEjecucion()
{
    return procesoEjecucion;
}

bool Memoria::llena()
{
    return curr_size>=MAX_SIZE;
}

void Memoria::desbloquear(Memoria::IteraProcesos pos)
{
    listos.push_back(move(*pos));
    bloqueados.erase(pos);

}
Memoria::Memoria(size_t MAX_SIZE):MAX_SIZE(MAX_SIZE),curr_size(0)
{
}



