#include "proceso.h"
#include <QtCore/qmath.h>
#include <QDebug>
Proceso::Proceso(QString nombreProgramador,int id,QString operando1,
                 QString operando2,Operador operador,
                 unsigned tiempo,QString resultado,bool resuelto)
    :nombreProgramador(nombreProgramador),id(id),
      operando1(operando1),operando2(operando2),operador(operador),
      maxTiempo(tiempo),resultado(resultado),resuelto(resuelto)
{
}

Proceso::Proceso(QString nombreProgramador,int id,QString operando1,
                 QString operando2,Operador operador,
                 unsigned tiempo)
    :Proceso(nombreProgramador,id,operando1,operando2,operador,tiempo,0,false)
{

}

std::unique_ptr<Proceso> Proceso::solve() const
{
    QString resultado;
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
            resultado=QString::number(operando1.toInt()%operando1.toInt());
            break;
    }
    return  std::unique_ptr<Proceso>(
                new Proceso(nombreProgramador,id,
                            operando1,operando2,operador,maxTiempo,
                            resultado,true));
}

Proceso::~Proceso()
{

}

QString Proceso::getResultado() const
{
    return resultado;
}

bool Proceso::estaResuelto() const
{
    return resuelto;
}

QString Proceso::getNombreProgramador() const
{
    return nombreProgramador;
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


