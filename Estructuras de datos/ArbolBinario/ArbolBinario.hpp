#ifndef ARBOLBINARIO_HPP
#define ARBOLBINARIO_HPP

#include <iostream>

// Tipo de elemento almacenado en el árbol
typedef int tipoElem;

// Estructura del nodo de un árbol binario
struct tNodoArbolBin {
    tipoElem info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

// Clase que representa el TDA Árbol Binario de Búsqueda (tABB)
class tABB {
private:
    tNodoArbolBin* raiz; // Puntero al nodo raíz del ABB
    int nElems;          // Cantidad de elementos en el ABB

    // Funciones auxiliares recursivas
    void clearHelp(tNodoArbolBin* nodo);
    int findHelp(tNodoArbolBin* nodo, tipoElem item) const;
    void inordenHelp(tNodoArbolBin* nodo) const;

public:
    // Constructor y Destructor
    tABB();
    ~tABB();

    // Métodos principales del TDA
    void clear();
    int find(tipoElem item) const;
    int size() const;

    // Recorridos
    void inorden() const;

    // Insertar
    void insertarhoja(int elemento);
};

#endif // ARBOLBINARIO_HPP