#include "proceso.h"
#include <QtCore/qmath.h>
#include <QDebug>
#include <sstream>
#include <string>
namespace std{
    std::string to_string(Proceso &p)
    {
        stringstream sstream;
        sstream<<p.getId()<<"|"<<"\n"<<
                 p.getOperando1().toStdString()
              <<" "<<static_cast<int>(p.getOperador())<<" "<<p.getOperando2().toStdString()
              <<"\n"<<p.getMaxTiempo()<<"s"<<"\n";
        if(p.estaResuelto()) sstream<<"R="<<p.getResultado().toStdString();
        return sstream.str();
    }
}
Proceso::Proceso(int id, QString operando1,
                 QString operando2, Operador operador,
                 unsigned tiempo, QString resultado, bool resuelto, int tiempoEjecucionRestante)
    :id(id),operando1(operando1),operando2(operando2),operador(operador),
      maxTiempo(tiempo),resultado(resultado),resuelto(resuelto),
      tiempoEjecucionRestante(tiempoEjecucionRestante)
    ,estado(Estado::ESPERA)
{
}

Proceso::Proceso(int id,QString operando1,
                 QString operando2,Operador operador,
                 unsigned tiempo)
    :Proceso(id,operando1,operando2,operador,tiempo,0,false,tiempo)
{

}



int Proceso::getTiempoEjecucionRestante() const
{
    return tiempoEjecucionRestante;
}


void Proceso::setTiempoEjecucionRestante(int value)
{
    tiempoEjecucionRestante = value;
}

void Proceso::avanzaEjecucion()
{
    if(!terminado())tiempoEjecucionRestante--;
}

bool Proceso::terminado() const
{
    return !getTiempoEjecucionRestante();
}

bool Proceso::bloquear(unsigned tiempo)
{
    tiempoBloqueoRestante=tiempo;
}

bool Proceso::bloqueado()
{
    return tiempoBloqueoRestante<=0;
}

void Proceso::avanzaTiempoBloqueo()
{
    tiempoBloqueoRestante--;
}
void Proceso::solve()
{
    switch(operador)
    {
    case Operador::SUMA:
        resultado=QString::number(operando1.toDouble()+operando2.toDouble());
            break;
        case Operador::RESTA:
            resultado=QString::number(operando1.toDouble()-operando2.toDouble());
            break;
        case Operador::MULTIPLICACION:
            resultado=QString::number(operando1.toDouble()*operando2.toDouble());
            break;
        case Operador::DIVISION:
            resultado=QString::number(operando1.toDouble()/operando2.toDouble());
            break;
        case Operador::RAIZ:
            resultado=QString::number(qSqrt(operando1.toDouble()));
            break;
        case Operador::RESTO:
            resultado=QString::number((int)operando1.toDouble()%
                                      (int)operando2.toDouble());
            break;
    }
}
bool Proceso::ocurrioError() const
{
    return estado==Estado::ERROR;
}
void Proceso::setOcurrioError()
{
    resultado="ERROR";
    estado=Estado::ERROR;
}

QString Proceso::getResultado() const
{
    return resultado;
}

bool Proceso::estaResuelto() const
{
    return resuelto;
}



int Proceso::getId() const
{
    return id;
}

QString Proceso::getOperando1() const
{
    return operando1;
}

QString Proceso::getOperando2() const
{
    return operando2;
}

Operador Proceso::getOperador() const
{
    return operador;
}

unsigned Proceso::getMaxTiempo() const
{
    return maxTiempo;
}
Proceso::~Proceso(){

}



