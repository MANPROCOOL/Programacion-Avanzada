#include "tPila.h"
#include <cstddef>

tPila::tPila() {
    tope = NULL;
    pilaSize = 0;
}

// Libera todos los nodos que hayan quedado en la pila.
tPila::~tPila() {
    while (tope != NULL) {
        tNodoPila* aux = tope;
        tope = tope->sig;
        delete aux;
    }
}

// Reinicializa la pila como vacía, liberando sus nodos.
void tPila::clear() {
    while (tope != NULL) {
        tNodoPila* aux = tope;
        tope = tope->sig;
        delete aux;
    }
    pilaSize = 0;
}

int tPila::push(tElemPila item) {
    tNodoPila* nuevo = new tNodoPila;
    nuevo->info = item;
    nuevo->sig = tope;
    tope = nuevo;
    pilaSize++;
    return 1;   // inserción exitosa
}

void tPila::pop() {
    if (tope == NULL) return;   // pila vacía: no hace nada
    tNodoPila* aux = tope;
    tope = tope->sig;
    delete aux;
    pilaSize--;
}

// Precondición: la pila no está vacía.
tElemPila tPila::topValue() {
    return tope->info;
}

bool tPila::vacia() const { return tope == NULL; }

int tPila::size() const { return (int)pilaSize; }
