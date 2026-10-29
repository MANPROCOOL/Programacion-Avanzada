#ifndef TDAS_CLASE08_TCOLA_HPP
#define TDAS_CLASE08_TCOLA_HPP

#include "tTipos.hpp"

// Cola FIFO enlazada de vertices, compatible con el BFS de la diapositiva 42.
class tCola {
public:
    tCola();
    ~tCola();
    tCola(const tCola& otra);
    tCola& operator=(const tCola& otra);
    void enqueue(tVertice valor);
    void dequeue(); // Elimina; el valor se consulta ANTES con frontValue().
    tVertice frontValue() const;
    int size() const;
    bool isEmpty() const;
    void clear();

private:
    struct Nodo { tVertice valor; Nodo* siguiente; };
    Nodo* frente_;
    Nodo* final_;
    int cantidad_;
};

#endif
