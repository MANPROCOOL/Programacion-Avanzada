#include "Pila.hpp"
#include <cassert>

// LIFO: ultimo en entrar, primero en salir.
tPila::tPila() : tope(nullptr), tam(0) {}

tPila::~tPila() { clear(); }

// Inserta en la cabeza de la lista. O(1).
int tPila::push(tElemPila item) {
    tNodo* nuevo = new tNodo;
    nuevo->info = item;
    nuevo->sig = tope;
    tope = nuevo;
    tam++;
    return 1;
}

// Elimina el tope sin retornar su valor. O(1).
void tPila::pop() {
    assert(tam > 0);
    tNodo* aux = tope;
    tope = tope->sig;
    delete aux;
    tam--;
}

// Consulta sin eliminar. O(1).
tElemPila tPila::topValue() const {
    assert(tam > 0);
    return tope->info;
}

int tPila::size() const { return tam; }

// Libera todos los nodos. O(n).
void tPila::clear() {
    while (tam > 0) {
        pop();
    }
}
