#ifndef TPILA_H
#define TPILA_H

// ─────────────────────────────────────────────────────────────────────────────
//  Pila (LIFO), enlazada
//  INF-20325 – Estructuras de Datos  |  UTFSM 2026-2
//
//  tope apunta al último elemento insertado (el próximo en salir).
// ─────────────────────────────────────────────────────────────────────────────

typedef int tElemPila;

struct tNodoPila {
    tElemPila  info;
    tNodoPila* sig;
};

class tPila {
    tNodoPila*   tope;
    unsigned int pilaSize;

public:
    tPila();
    ~tPila();

    void clear();                // reinicializa la pila como vacía
    int  push(tElemPila item);   // agrega un elemento en el tope — O(1)
    void pop();                  // elimina el elemento del tope — O(1)
    tElemPila topValue();        // retorna el valor del tope (no lo elimina)
    bool vacia() const;
    int  size() const;
};

#endif // TPILA_H
