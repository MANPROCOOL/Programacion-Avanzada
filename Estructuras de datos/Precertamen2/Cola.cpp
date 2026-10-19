#include "Cola.hpp"
#include <cassert>

// FIFO: primero en entrar, primero en salir.
tCola::tCola() : frente(nullptr), fin(nullptr), tam(0) {}

tCola::~tCola() { clear(); }

// Inserta al final. O(1).
int tCola::enqueue(tElemCola item) {
    tNodo* nuevo = new tNodo;
    nuevo->info = item;
    nuevo->sig = nullptr;

    if (tam == 0) {
        frente = nuevo;
    } else {
        fin->sig = nuevo;
    }
    fin = nuevo;
    tam++;
    return 1;
}

// Elimina el frente sin retornar su valor. O(1).
void tCola::dequeue() {
    assert(tam > 0);
    tNodo* aux = frente;
    frente = frente->sig;
    delete aux;
    tam--;

    // Si se elimino el ultimo nodo, ambos extremos quedan vacios.
    if (tam == 0) {
        fin = nullptr;
    }
}

// Consulta sin eliminar. O(1).
tElemCola tCola::frontValue() const {
    assert(tam > 0);
    return frente->info;
}

int tCola::size() const { return tam; }

// Libera todos los nodos. O(n).
void tCola::clear() {
    while (tam > 0) {
        dequeue();
    }
}
