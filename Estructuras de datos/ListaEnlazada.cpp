#include "ListaEnlazada.hpp"

// Constructor: Inicializa la lista vacía con un nodo centinela
tLista::tLista() {
    curr = tail = head = new tNodo;
    head->sig = NULL;
    listSize = 0;
    pos = 0;
}

// Destructor: Libera toda la memoria dinámica utilizada
tLista::~tLista() {
    clear();
    delete head; // Elimina el nodo centinela
}

// Vacía la lista y libera la memoria de los nodos con elementos
void tLista::clear() {
    moveToStart();
    while (head->sig != NULL) {
        tNodo* temp = head->sig;
        head->sig = temp->sig;
        delete temp;
    }
    curr = tail = head;
    listSize = 0;
    pos = 0;
}

// Inserta un elemento en la posición actual de 'curr'
int tLista::insert(tElemLista item) {
    tNodo* aux = new tNodo;
    aux->info = item;
    aux->sig = curr->sig;
    curr->sig = aux;

    if (tail == curr) {
        tail = curr->sig; // Actualiza tail si se inserta al final
    }

    listSize++;
    return pos;
}

// Agrega un elemento al final de la lista
void tLista::append(tElemLista item) {
    tNodo* aux = new tNodo;
    aux->info = item;
    aux->sig = NULL;

    tail->sig = aux;
    tail = aux;
    listSize++;
}

// Reemplaza el elemento en la posición actual
void tLista::replace(tElemLista item) {
    if (curr->sig != NULL) {
        curr->sig->info = item;
    }
}

// Elimina el elemento actual y lo retorna
tElemLista tLista::erase() {
    if (curr->sig == NULL) {
        return '\0'; // Retorna el carácter nulo si no hay elemento a borrar
    }

    tNodo* temp = curr->sig;
    tElemLista item = temp->info;

    if (tail == temp) {
        tail = curr; // Si se borra el último elemento, se actualiza tail
    }

    curr->sig = temp->sig;
    delete temp;
    listSize--;

    return item;
}

// Mueve la posición actual al inicio de la lista
void tLista::moveToStart() {
    curr = head;
    pos = 0;
}

// Mueve la posición actual al final de la lista
void tLista::moveToEnd() {
    curr = tail;
    pos = listSize;
}

// Retrocede una posición el puntero 'curr'
void tLista::prev() {
    if (curr == head) return;

    tNodo* temp = head;
    while (temp->sig != curr) {
        temp = temp->sig;
    }
    curr = temp;
    pos--;
}

// Avanza una posición el puntero 'curr'
void tLista::next() {
    if (curr != tail) {
        curr = curr->sig;
        pos++;
    }
}

// Mueve el cursor 'curr' a una posición p
void tLista::moveToPos(unsigned int p) {
    if (p > listSize) return;

    curr = head;
    pos = 0;
    for (unsigned int i = 0; i < p; i++) {
        curr = curr->sig;
        pos++;
    }
}

// Retorna la cantidad de elementos en la lista
unsigned int tLista::length() const {
    return listSize;
}

// Retorna la posición actual
unsigned int tLista::currPos() const {
    return pos;
}

// Obtiene el valor del elemento actual
tElemLista tLista::getValue() const {
    if (curr->sig == NULL) {
        return '\0'; // Retorna el carácter nulo si está en la posición final o vacía
    }
    return curr->sig->info;
}

// Invierte la lista
void tLista::invertirforma1(){

    char aux1, aux2;
    moveToStart();
    for (int i = 0; i < listSize; i++){
        moveToPos(i);
        aux1 = getValue();
        moveToPos(listSize - i);
        aux2 = getValue();
        replace(aux1);
        moveToPos(i);
        replace(aux2);
    }
}