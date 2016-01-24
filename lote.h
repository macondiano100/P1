#ifndef LOTE_H
#define LOTE_H
#include <list>
#include <memory>
#include <iterator>
#include "proceso.h"
class Lote
{
public:
    using Proceso_ptr=std::shared_ptr<Proceso>;
    using iterator=std::list<Proceso_ptr>::iterator;
    Lote(unsigned maxSize);
    unsigned getMaxSize() const;
    void push(Proceso_ptr proceso);
    Proceso_ptr pop();
    iterator begin();
    iterator end();
    bool empty();
    size_t size();
    ~Lote();
private:
    std::list<Proceso_ptr> procesos;
    const unsigned maxSize;
};

#endif // LOTE_H
