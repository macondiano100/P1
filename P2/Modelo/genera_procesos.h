#ifndef GENERA_PROCESOS_H
#define GENERA_PROCESOS_H
#include <proceso.h>
#include <memory>
#include <random>
#include <array>
class GeneradorProcesos
{
    int cantidad;
    int contadorId;
    std::random_device rd;
    std::mt19937 int_generator;
    std::uniform_int_distribution<int> distOperandos;
    std::uniform_int_distribution<int> distOperadores;
    std::uniform_int_distribution<int> distTiempo;

public:
    explicit GeneradorProcesos(int cantidad):cantidad(cantidad),
        contadorId(0),int_generator(rd()),distOperandos(-10000,10000),
        distOperadores(static_cast<int>(Operador::SUMA),static_cast<int>(Operador::RESTO)),
        distTiempo(1,30)
    {
    }
    bool finished()
    {
        return contadorId==cantidad;
    }
    std::shared_ptr<Proceso> next()
    {
       return std::make_shared<Proceso>("",++contadorId,
                    QString::number(distOperandos(int_generator)),
                    QString::number(distOperandos(int_generator)),
                    static_cast<Operador>(distOperadores(int_generator)),
                    distTiempo(int_generator)
                    );
    }
};

#endif // GENERA_PROCESOS_H
