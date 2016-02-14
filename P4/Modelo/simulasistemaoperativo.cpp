#include "Modelo/simulasistemaoperativo.h"

SimulaSistemaOperativo::SimulaSistemaOperativo(QObject *parent) : QObject(parent),memoria(4),
    finalizado(false)
{
    insertaProcesosAMemoria();
    actualizaProcesoEnEjecucion();
}

SimulaSistemaOperativo::~SimulaSistemaOperativo()
{

}

void SimulaSistemaOperativo::agregaProceso(std::unique_ptr<Proceso> &&proceso)
{
    creados.push_back(move(proceso));
    insertaProcesosAMemoria();
}

void SimulaSistemaOperativo::actualizaProcesoEnEjecucion()
{
    auto& procesoEjecutandose=memoria.getProcesoEjecucion();
    if(procesoEjecutandose==nullptr){
        if(memoria.sizeProcesosListos()==0)return;
        memoria.ejecutaSiguiente();
        auto& procesoEjecutandose=memoria.getProcesoEjecucion();
        if(tiempos[procesoEjecutandose->getId()].segundoInicio==infoTiempoProceso::npos)
           tiempos[procesoEjecutandose->getId()].segundoInicio=segundoActual;

    }
}

void SimulaSistemaOperativo::insertaProcesosAMemoria()
{
    auto beginProcesosCreados=creados.begin(),endCreados=creados.end();
    auto& procesoEjecutandose=memoria.getProcesoEjecucion();
    while(!memoria.llena()&&beginProcesosCreados!=endCreados)
    {
        tiempos[(*beginProcesosCreados)->getId()].segundoLlegada=segundoActual;
        memoria.agregaProceso(move(*beginProcesosCreados));
        beginProcesosCreados=creados.erase(beginProcesosCreados);
    }
}

void SimulaSistemaOperativo::actualizaProcesosBloqueados()
{
    auto beginBloqueados=memoria.beginProcesosBloqueados();
    auto endBloqueados=memoria.endProcesosBloqueados();
    while(beginBloqueados!=endBloqueados)
    {
        (*beginBloqueados)->avanzaTiempoBloqueo();
        if(!((*beginBloqueados)->bloqueado()))
        {
            memoria.desbloquear(beginBloqueados);
        }
        beginBloqueados++;
    }
}

void SimulaSistemaOperativo::forzarError()
{
    auto &procesoEjecutandose=memoria.getProcesoEjecucion();
    if(procesoEjecutandose!=nullptr)
    {
        tiempos[procesoEjecutandose->getId()].segundoFinalizacion=segundoActual;
        tiempos[procesoEjecutandose->getId()].tiempoServicio=
                tiempos[procesoEjecutandose->getId()].tiempoServicio-
                procesoEjecutandose->getTiempoEjecucionRestante();
        terminados.push_back(move(memoria.errorEjecucion()));
        actualizaProcesoEnEjecucion();
    }
}

bool SimulaSistemaOperativo::simulacionTerminada()
{
    return  finalizado=
            memoria.getProcesoEjecucion()==nullptr&&
            creados.empty()&&
            beginProcesosBloqueados()==endProcesosBloqueados()&&
            beginProcesosListos()==endProcesosListos();
}

SimulaSistemaOperativo::Registro_Tiempos SimulaSistemaOperativo::dameRegitroTiempos()
{
    return tiempos;
}

size_t SimulaSistemaOperativo::sizeProcesosCreados()
{
    return creados.size();
}

void SimulaSistemaOperativo::actualizaProcesosListos()
{
    auto beginListos=memoria.beginProcesosListos();
    auto endListos=memoria.endProcesosListos();
    while(beginListos!=endListos)
    {
        beginListos++;
    }
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::beginProcesosListos()
{
    return memoria.beginProcesosListos();
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::endProcesosListos()
{
    return memoria.endProcesosListos();
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::beginProcesosTerminados()
{
    return terminados.begin();
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::endProcesosTerminados()
{
    return terminados.end();
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::beginProcesosBloqueados()
{
    return memoria.beginProcesosBloqueados();
}

SimulaSistemaOperativo::IteraProcesos SimulaSistemaOperativo::endProcesosBloqueados()
{
    return memoria.endProcesosBloqueados();
}

void SimulaSistemaOperativo::bloqueaProceso(unsigned t)
{
    memoria.bloqueaEjecucion(t);
    actualizaProcesoEnEjecucion();
}

std::unique_ptr<Proceso>& SimulaSistemaOperativo::getProcesoEnEjecucion()
{
    return memoria.getProcesoEjecucion();
}

#include <QDebug>
void SimulaSistemaOperativo::clock()
{
    segundoActual++;
    auto& procesoEjecutandose=memoria.getProcesoEjecucion();
    if(procesoEjecutandose!=nullptr)
    {
        procesoEjecutandose->avanzaEjecucion();
        if(procesoEjecutandose->terminado()){
            procesoEjecutandose=memoria.resuelveProcesoEnEjecucion();
            tiempos[procesoEjecutandose->getId()].segundoFinalizacion=segundoActual;
            terminados.push_back(move(procesoEjecutandose));
        }
    }

    insertaProcesosAMemoria();
    actualizaProcesosListos();
    actualizaProcesosBloqueados();
    actualizaProcesoEnEjecucion();

}



void Memoria::ejecutaSiguiente()
{
    if(!listos.empty())
    {
        procesoEjecucion=std::move(listos.front());
        listos.pop_front();
    }
}

std::unique_ptr<Proceso> Memoria::resuelveProcesoEnEjecucion()
{

    if(procesoEjecucion!=nullptr)
    {
        procesoEjecucion->solve();
        curr_size--;
        return std::move(procesoEjecucion);
    }
    return nullptr;
}

void Memoria::bloqueaEjecucion(unsigned t)
{
   if(procesoEjecucion)
   {
       procesoEjecucion->bloquear(t);
       bloqueados.push_back(std::move(procesoEjecucion));
   }
}

std::unique_ptr<Proceso> Memoria::errorEjecucion()
{
    if(procesoEjecucion)
    {
        procesoEjecucion->setOcurrioError();
        curr_size--;
        return std::move(procesoEjecucion);
    }
    return nullptr;
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



size_t Memoria::sizeProcesosListos()
{
    return listos.size();
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
    qDebug()<<"Desbloquea "<<(*pos)->getId();
    listos.push_back(move(*pos));
    bloqueados.erase(pos);

}
Memoria::Memoria(size_t MAX_SIZE):curr_size(0),MAX_SIZE(MAX_SIZE)
{
}



