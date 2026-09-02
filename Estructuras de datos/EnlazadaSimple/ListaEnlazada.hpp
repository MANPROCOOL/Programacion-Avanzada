#ifndef LISTAENLAZADA_HPP
#define LISTAENLAZADA_HPP

#include <iostream>

// Tipo de dato almacenado en la lista (reemplaza 'int' por 'char')
typedef char tElemLista;

// Nodo de la lista enlazada
struct tNodo {
    tElemLista info;
    tNodo* sig;
};

class tLista {
private:
    tNodo* head;           // Puntero al nodo centinela (inicio)
    tNodo* tail;           // Puntero al último nodo
    tNodo* curr;           // Puntero al nodo previo a la posición actual
    unsigned int listSize; // Tamaño actual de la lista
    unsigned int pos;      // Posición lógica actual (0 <= pos <= listSize)

public:
    // Constructor y Destructor
    tLista();
    ~tLista();

    // Métodos de modificación de estado
    void clear();
    int insert(tElemLista item);
    void append(tElemLista item);
    tElemLista erase();
    
    // Reemplaza el elemento en la posición actual por el nuevo 'item'
    void replace(tElemLista item);

    // Métodos de navegación y posicionamiento
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    void moveToPos(unsigned int p);

    // Métodos de consulta
    unsigned int length() const;
    unsigned int currPos() const;
    tElemLista getValue() const;

    // Invertir
    void invertirforma1();
    void invertirforma2();
};

#endif // LISTAENLAZADA_HPP