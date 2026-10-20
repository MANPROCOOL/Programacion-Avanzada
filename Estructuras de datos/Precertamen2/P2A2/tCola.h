#ifndef TCOLA_H
#define TCOLA_H

// ─────────────────────────────────────────────────────────────────────────────
//  Cola (FIFO), enlazada
//  INF-20325 – Estructuras de Datos  |  UTFSM 2026-2
//
//  frente apunta al próximo elemento en salir; final, al último en entrar.
// ─────────────────────────────────────────────────────────────────────────────

typedef int tElemCola;

struct tNodoCola {
    tElemCola  info;
    tNodoCola* sig;
};

class tCola {
    tNodoCola*   frente;
    tNodoCola*   final;
    unsigned int colaSize;

public:
    tCola();
    ~tCola();

    void clear();                   // reinicializa la cola como vacía
    int  enqueue(tElemCola item);   // agrega un elemento al final — O(1)
    void dequeue();                 // elimina el elemento del frente — O(1)
    tElemCola frontValue();         // retorna el valor del frente (no lo elimina)
    bool vacia() const;
    int  size() const;
    void print();                   // imprime todos los elementos separados por espacio
};

#endif // TCOLA_H
