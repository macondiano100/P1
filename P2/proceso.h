#ifndef PROCESO_H
#define PROCESO_H
#include <QString>
#include <memory>
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
    int tiempoEjecucionRestante;
public:
    std::unique_ptr<Proceso> solve() const;
    ~Proceso();
    bool estaResuelto() const;
    QString getNombreProgramador() const ;
    int getId() const;
    QString getOperando1() const;
    QString getOperando2() const;
    Operador getOperador() const;
    unsigned getMaxTiempo() const;
    QString getResultado() const;
    Proceso(QString nombreProgramador, int id,
            QString operando1, QString operando2,
            Operador operador, unsigned tiempo);

    int getTiempoEjecucionRestante() const;
    void setTiempoEjecucionRestante(int value);

private:
    Proceso(QString nombreProgramador, int id,
            QString operando1, QString operando2,
            Operador operador, unsigned tiempo,
            QString resultado, bool resuelto,int tiempoEjecucionRestante);
};
namespace std {
std::string to_string(Proceso &p);
}
#endif // PROCESO_H
