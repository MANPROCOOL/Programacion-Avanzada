#ifndef LISTAENLAZADADOBLE_HPP
#define LISTAENLAZADADOBLE_HPP

#include <iostream>

typedef char tElemLista;

// Nodo de la lista doblemente enlazada
struct tNodo {
    tElemLista info;
    tNodo* sig;
    tNodo* ant; // Puntero al nodo anterior
};

class tLista {
private:
    tNodo* head;           // Nodo centinela inicial
    tNodo* tail;           // Puntero al último nodo
    tNodo* curr;           // Puntero al nodo previo a la posición actual
    unsigned int listSize; // Tamaño actual de la lista
    unsigned int pos;      // Posición lógica actual (0 <= pos <= listSize)

public:
    tLista();
    ~tLista();

    void clear();
    int insert(tElemLista item);
    void append(tElemLista item);
    tElemLista erase();
    void replace(tElemLista item);

    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    void moveToPos(unsigned int p);

    unsigned int length() const;
    unsigned int currPos() const;
    tElemLista getValue() const;

    void invertirforma1();
};

#endif // LISTAENLAZADA_HPP