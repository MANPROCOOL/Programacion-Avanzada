#include "tCola.h"
#include <cstddef>
#include <iostream>

tCola::tCola() {
    frente = NULL;
    final = NULL;
    colaSize = 0;
}

// Libera todos los nodos que hayan quedado en la cola.
tCola::~tCola() {
    while (frente != NULL) {
        tNodoCola* aux = frente;
        frente = frente->sig;
        delete aux;
    }
}

// Reinicializa la cola como vacía, liberando sus nodos.
void tCola::clear() {
    while (frente != NULL) {
        tNodoCola* aux = frente;
        frente = frente->sig;
        delete aux;
    }
    final = NULL;
    colaSize = 0;
}

int tCola::enqueue(tElemCola item) {
    tNodoCola* nuevo = new tNodoCola;
    nuevo->info = item;
    nuevo->sig = NULL;
    if (final == NULL) {
        frente = final = nuevo;
    } else {
        final->sig = nuevo;
        final = nuevo;
    }
    colaSize++;
    return 1;   // inserción exitosa
}

void tCola::dequeue() {
    if (frente == NULL) return;   // cola vacía: no hace nada
    tNodoCola* aux = frente;
    frente = frente->sig;
    if (frente == NULL) final = NULL;
    delete aux;
    colaSize--;
}

// Precondición: la cola no está vacía.
tElemCola tCola::frontValue() {
    return frente->info;
}

bool tCola::vacia() const { return frente == NULL; }

int tCola::size() const { return (int)colaSize; }

void tCola::print() {
    bool first = true;
    for (tNodoCola* n = frente; n != NULL; n = n->sig) {
        if (!first) std::cout << " ";
        std::cout << n->info;
        first = false;
    }
    std::cout << std::endl;
}
