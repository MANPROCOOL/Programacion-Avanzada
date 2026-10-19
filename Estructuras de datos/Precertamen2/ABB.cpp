#include "ABB.hpp"
#include <iostream>

tABB::tABB() : raiz(nullptr), nElems(0) {}
tABB::~tABB() { clear(); }

void tABB::clearHelp(tNodo* nodo) {
    if (nodo == nullptr) return;
    clearHelp(nodo->izq);
    clearHelp(nodo->der);
    delete nodo;
}

void tABB::clear() {
    clearHelp(raiz);
    raiz = nullptr;
    nElems = 0;
}

// Sigue la busqueda hasta un enlace vacio; alli inserta una hoja.
void tABB::insert(tipoElem item) {
    tNodo** enlace = &raiz;
    while (*enlace != nullptr) {
        if (item == (*enlace)->info) return;
        if (item < (*enlace)->info) enlace = &(*enlace)->izq;
        else enlace = &(*enlace)->der;
    }
    *enlace = new tNodo{item, nullptr, nullptr};
    nElems++;
}

int tABB::find(tipoElem item) const {
    tNodo* nodo = raiz;
    while (nodo != nullptr) {
        if (item == nodo->info) return 1;
        if (item < nodo->info) nodo = nodo->izq;
        else nodo = nodo->der;
    }
    return 0;
}

void tABB::remove(tipoElem item) {
    tNodo** enlace = &raiz;
    while (*enlace != nullptr && (*enlace)->info != item) {
        if (item < (*enlace)->info) enlace = &(*enlace)->izq;
        else enlace = &(*enlace)->der;
    }
    if (*enlace == nullptr) return;
    tNodo* borrar = *enlace;

    if (borrar->izq != nullptr && borrar->der != nullptr) {
        // Dos hijos: reemplaza el valor con su sucesor en inorden.
        tNodo** sucesor = &borrar->der;
        while ((*sucesor)->izq != nullptr) sucesor = &(*sucesor)->izq;
        borrar->info = (*sucesor)->info;
        borrar = *sucesor;
        *sucesor = borrar->der;
    } else {
        // Cero o un hijo: el enlace adopta al hijo que exista.
        *enlace = (borrar->izq != nullptr) ? borrar->izq : borrar->der;
    }
    delete borrar;
    nElems--;
}

int tABB::size() const { return nElems; }
tNodo* tABB::getRaiz() const { return raiz; }

void tABB::inOrdenHelp(tNodo* nodo) {
    if (nodo == nullptr) return;
    inOrdenHelp(nodo->izq);
    std::cout << nodo->info << ' ';
    inOrdenHelp(nodo->der);
}
void tABB::preOrdenHelp(tNodo* nodo) {
    if (nodo == nullptr) return;
    std::cout << nodo->info << ' ';
    preOrdenHelp(nodo->izq);
    preOrdenHelp(nodo->der);
}
void tABB::postOrdenHelp(tNodo* nodo) {
    if (nodo == nullptr) return;
    postOrdenHelp(nodo->izq);
    postOrdenHelp(nodo->der);
    std::cout << nodo->info << ' ';
}
void tABB::inOrden() const { inOrdenHelp(raiz); }
void tABB::preOrden() const { preOrdenHelp(raiz); }
void tABB::postOrden() const { postOrdenHelp(raiz); }
