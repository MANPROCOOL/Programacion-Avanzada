#include <iostream>

// Estructura de datos que almacena la información del elemento
struct tElemLista {
    int clave;
};

// Nodo de la lista enlazada
struct tNodo {
    tElemLista info;
    tNodo* sig;
};

class tLista {
private:
    tNodo* head;           // Puntero al nodo centinela (inicio de la lista)
    tNodo* tail;           // Puntero al último nodo de la lista
    tNodo* curr;           // Puntero al nodo previo a la posición actual
    unsigned int listSize; // Tamaño actual de la lista
    unsigned int pos;      // Posición lógica actual (0 <= pos <= listSize)

public:
    // Constructor: Inicializa la lista vacía con un nodo centinela
    tLista() {
        curr = tail = head = new tNodo;
        head->sig = NULL;
        listSize = 0;
        pos = 0;
    }

    // Destructor: Libera toda la memoria dinámica utilizada por los nodos
    ~tLista() {
        clear();
        delete head; // Elimina el nodo centinela
    }

    // Vacía la lista y libera la memoria de los nodos con elementos
    void clear() {
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
    int insert(tElemLista item) {
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
    void append(tElemLista item) {
        tNodo* aux = new tNodo;
        aux->info = item;
        aux->sig = NULL;

        tail->sig = aux;
        tail = aux;
        listSize++;
    }

    // Elimina el elemento actual y lo retorna
    tElemLista erase() {
        if (curr->sig == NULL) {
            tElemLista vacio = {-1};
            return vacio;
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
    void moveToStart() {
        curr = head;
        pos = 0;
    }

    // Mueve la posición actual al final de la lista
    void moveToEnd() {
        curr = tail;
        pos = listSize;
    }

    // Retrocede una posición el puntero 'curr'
    void prev() {
        if (curr == head) return;

        tNodo* temp = head;
        while (temp->sig != curr) {
            temp = temp->sig;
        }
        curr = temp;
        pos--;
    }

    // Avanza una posición el puntero 'curr'
    void next() {
        if (curr != tail) {
            curr = curr->sig;
            pos++;
        }
    }

    // Mueve el cursor 'curr' a una posición p
    void moveToPos(unsigned int p) {
        if (p > listSize) return;

        curr = head;
        pos = 0;
        for (unsigned int i = 0; i < p; i++) {
            curr = curr->sig;
            pos++;
        }
    }

    // Retorna la cantidad de elementos en la lista
    unsigned int length() {
        return listSize;
    }

    // Retorna la posición actual
    unsigned int currPos() {
        return pos;
    }

    // Obtiene el valor del elemento actual
    tElemLista getValue() {
        if (curr->sig == NULL) {
            tElemLista vacio = {-1};
            return vacio;
        }
        return curr->sig->info;
    }
};
