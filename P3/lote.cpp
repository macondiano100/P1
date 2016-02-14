#include "lote.h"
#include <string>
#include <sstream>

Lote::Lote(unsigned maxSize):maxSize(maxSize)
{

}

unsigned Lote::getMaxSize() const
{
    return getMaxSize();
}
void Lote::push(Proceso_ptr proceso)
{
    procesos.push_back(proceso);
}
Lote::Proceso_ptr Lote::pop()
{
    auto p=procesos.front();
    procesos.pop_front();
    return p;
}

Lote::iterator Lote::begin()
{
    return procesos.begin();
}

Lote::iterator Lote::end()
{
    return procesos.end();
}

bool Lote::empty()
{
    return procesos.empty();
}

size_t Lote::size()
{
    return procesos.size();
}

Lote::~Lote()
{

}






