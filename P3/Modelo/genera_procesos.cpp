#include "genera_procesos.h"
#include <memory>




GeneradorProcesos::GeneradorProcesos(int cantidad):cantidad(cantidad),
    contadorId(0),
    rd(),
    int_generator(rd()),
    distOperadores(static_cast<int>(Operador::SUMA),static_cast<int>(Operador::RESTO)),
    distTiempo(5,10)
{
}

bool GeneradorProcesos::finished()
{
    return contadorId==cantidad;
}

std::shared_ptr<Proceso> GeneradorProcesos::next()
{
    Operador op=static_cast<Operador>(distOperadores(int_generator));
    std::unique_ptr<std::uniform_int_distribution<int>> distOperandos;
    if(op==Operador::RAIZ)
    {
        distOperandos.reset(new std::uniform_int_distribution<int>(0,100));
    }
    else distOperandos.reset(new std::uniform_int_distribution<int>(-100,100));
    return finished()?nullptr:
                      std::make_shared<Proceso>("",contadorId++,
                                                QString::number((*distOperandos)(int_generator)),
                                                QString::number((*distOperandos)(int_generator)),
                                                op,
                                                distTiempo(int_generator)
                                                );

}
