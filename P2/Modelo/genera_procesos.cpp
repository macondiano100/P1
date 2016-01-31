#include "genera_procesos.h"





GeneradorProcesos::GeneradorProcesos(int cantidad):cantidad(cantidad),
    contadorId(0),
    rd(),
    int_generator(rd()),distOperandos(-10000,10000),
    distOperadores(static_cast<int>(Operador::SUMA),static_cast<int>(Operador::RESTO)),
    distTiempo(1,30)
{
}

bool GeneradorProcesos::finished()
{
    return contadorId==cantidad;
}

std::shared_ptr<Proceso> GeneradorProcesos::next()
{
    /*
         * TODO
         * Validar casos de operandos inválidos
        */
    return finished()?nullptr:
                      std::make_shared<Proceso>("",contadorId++,
                                                QString::number(distOperandos(int_generator)),
                                                QString::number(distOperandos(int_generator)),
                                                static_cast<Operador>(distOperadores(int_generator)),
                                                distTiempo(int_generator)
                                                );

}
