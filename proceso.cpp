#include "proceso.h"
#include <QtCore/qmath.h>

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

Proceso Proceso::solve()
{
    QString resultado;
    switch(operador)
    {
        case Operador::SUMA:
            resultado=operando1.toDouble()+operando2.toDouble();
            break;
        case Operador::RESTA:
            resultado=operando1.toDouble()-operando2.toDouble();
            break;
        case Operador::MULTIPLICACION:
            resultado=operando1.toDouble()*operando2.toDouble();
            break;
        case Operador::DIVISION:
            resultado=operando1.toDouble()/operando2.toDouble();
            break;
        case Operador::RAIZ:
            resultado=qSqrt(operando1.toDouble());
            break;
        case Operador::RESTO:
            resultado=operando1.toInt()%operando1.toInt();
            break;
    }
    return Proceso(nombreProgramador,id,operando1,operando2,operador,maxTiempo,
                   resultado,true);
}

Proceso::~Proceso()
{

}

