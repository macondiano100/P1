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
    explicit GeneradorProcesos(int cantidad);
    bool finished();
    std::shared_ptr<Proceso> next();
};

#endif // GENERA_PROCESOS_H
