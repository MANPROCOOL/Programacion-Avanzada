#include "ListaEnlazadaDoble.hpp"

// Constructor
tLista::tLista() {
    curr = tail = head = new tNodo;
    head->sig = NULL;
    head->ant = NULL;
    listSize = 0;
    pos = 0;
}

// Destructor
tLista::~tLista() {
    clear();
    delete head;
}

// Vacía la lista
void tLista::clear() {
    moveToStart();
    while (head->sig != NULL) {
        tNodo* temp = head->sig;
        head->sig = temp->sig;
        delete temp;
    }
    head->sig = NULL;
    curr = tail = head;
    listSize = 0;
    pos = 0;
}

// Inserta después de 'curr'
int tLista::insert(tElemLista item) {
    tNodo* aux = new tNodo;
    aux->info = item;
    aux->sig = curr->sig;
    aux->ant = curr;

    if (curr->sig != NULL) {
        curr->sig->ant = aux;
    }
    curr->sig = aux;

    if (tail == curr) {
        tail = aux;
    }

    listSize++;
    return pos;
}

// Agrega al final de la lista
void tLista::append(tElemLista item) {
    tNodo* aux = new tNodo;
    aux->info = item;
    aux->sig = NULL;
    aux->ant = tail;

    tail->sig = aux;
    tail = aux;
    listSize++;
}

// Reemplaza el elemento actual
void tLista::replace(tElemLista item) {
    if (curr->sig != NULL) {
        curr->sig->info = item;
    }
}

// Elimina el elemento actual
tElemLista tLista::erase() {
    if (curr->sig == NULL) {
        return '\0';
    }

    tNodo* temp = curr->sig;
    tElemLista item = temp->info;

    curr->sig = temp->sig;
    if (temp->sig != NULL) {
        temp->sig->ant = curr;
    } else {
        tail = curr;
    }

    delete temp;
    listSize--;
    return item;
}

void tLista::moveToStart() {
    curr = head;
    pos = 0;
}

void tLista::moveToEnd() {
    curr = tail;
    pos = listSize;
}

// Retroceso optimizado a O(1) usando el puntero 'ant'
void tLista::prev() {
    if (curr != head) {
        curr = curr->ant;
        pos--;
    }
}

void tLista::next() {
    if (curr != tail) {
        curr = curr->sig;
        pos++;
    }
}

void tLista::moveToPos(unsigned int p) {
    if (p > listSize) return;

    curr = head;
    pos = 0;
    for (unsigned int i = 0; i < p; i++) {
        curr = curr->sig;
        pos++;
    }
}

unsigned int tLista::length() const {
    return listSize;
}

unsigned int tLista::currPos() const {
    return pos;
}

tElemLista tLista::getValue() const {
    if (curr->sig == NULL) {
        return '\0';
    }
    return curr->sig->info;
}

void tLista::invertirforma1() {
    char aux1, aux2;
    for (unsigned int i = 0; i < listSize / 2; i++) {
        moveToPos(i);
        aux1 = getValue();
        moveToPos(listSize - i - 1);
        aux2 = getValue();
        replace(aux1);
        moveToPos(i);
        replace(aux2);
    }
}