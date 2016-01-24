#ifndef PROCESO_H
#define PROCESO_H
#include <QString>
enum class Operador{
    SUMA=1,
    RESTA,
    MULTIPLICACION,
    DIVISION,
    RAIZ,
    RESTO
};

class Proceso
{
    const QString nombreProgramador;
    const int id;
    const QString operando1;
    const QString operando2;
    const Operador operador;
    const unsigned maxTiempo;
    const QString resultado;
    const bool resuelto;
    Proceso(QString,QString,Operador,unsigned,QString);
public:
    Proceso solve();
    ~Proceso();
    Proceso(QString nombreProgramador, int id,
            QString operando1, QString operando2,
            Operador operador, unsigned tiempo);
private:
    Proceso(QString nombreProgramador, int id,
            QString operando1, QString operando2,
            Operador operador, unsigned tiempo,
            QString resultado, bool resuelto);
};

#endif // PROCESO_H
