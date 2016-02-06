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
enum class Estado
{
    ESPERA,EJECUCION,ERROR
};
class Proceso
{
    const QString nombreProgramador;
    const int id;
    const QString operando1;
    const QString operando2;
    const Operador operador;
    const unsigned maxTiempo;
    QString resultado;
    bool resuelto;
    int tiempoEjecucionRestante;
    Estado estado;
public:
    void solve();
    bool ocurrioError() const;
    void setOcurrioError();
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
    void avanzaEjecucion();
    bool terminado() const;
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
