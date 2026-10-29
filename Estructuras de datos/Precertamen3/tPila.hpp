#ifndef TDAS_CLASE08_TPILA_HPP
#define TDAS_CLASE08_TPILA_HPP

#include "tTipos.hpp"

// Pila LIFO enlazada de vertices para DFS iterativo.
class tPila {
public:
    tPila();
    ~tPila();
    tPila(const tPila& otra);
    tPila& operator=(const tPila& otra);
    void push(tVertice valor);
    void pop(); // Elimina; el valor se consulta ANTES con topValue().
    tVertice topValue() const;
    int size() const;
    bool isEmpty() const;
    void clear();

private:
    struct Nodo { tVertice valor; Nodo* siguiente; };
    Nodo* tope_;
    int cantidad_;
};

#endif
