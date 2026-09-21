#include "ArbolBinario.hpp"

// Función auxiliar para procesar el valor de un nodo durante los recorridos
static void procesar(tipoElem info) {
    std::cout << info << " ";
}

// Constructor: Inicializa el árbol vacío
tABB::tABB() {
    raiz = nullptr;
    nElems = 0;
}

// Destructor: Libera toda la memoria dinámica utilizada por los nodos
tABB::~tABB() {
    clear();
}

// Función auxiliar recursiva para eliminar los nodos del árbol en post-orden
void tABB::clearHelp(tNodoArbolBin* nodo) {
    if (nodo == nullptr) return; // Árbol vacío o llegada a hoja, se detiene
    clearHelp(nodo->izq);        // Visita subárbol izquierdo recursivamente
    clearHelp(nodo->der);        // Visita subárbol derecho recursivamente
    delete nodo;                 // Después de borrar subárboles, se borra a sí mismo
}

// Elimina todos los elementos de un ABB dejándolo vacío
void tABB::clear() {
    clearHelp(raiz); // Función auxiliar para eliminar los nodos
    raiz = nullptr;
    nElems = 0;
}

// Función auxiliar recursiva para buscar un elemento en el árbol
int tABB::findHelp(tNodoArbolBin* nodo, tipoElem item) const {
    if (nodo == nullptr) return 0; // Item no está en el ABB
    if (nodo->info == item) return 1; // Item encontrado
    
    if (item < nodo->info) {
        return findHelp(nodo->izq, item);
    } else {
        return findHelp(nodo->der, item);
    }
}

// Busca un "item" en un ABB, retorna 1 si lo encuentra y 0 en caso contrario
int tABB::find(tipoElem item) const {
    return findHelp(raiz, item);
}

// Retorna la cantidad de elementos almacenados en el árbol
int tABB::size() const {
    return nElems;
}

// Función auxiliar recursiva para el recorrido in-orden
void tABB::inordenHelp(tNodoArbolBin* nodo) const {
    if (nodo == nullptr) return;
    inordenHelp(nodo->izq);   // Visita hijo izquierdo en in-orden
    procesar(nodo->info);     // Procesa nodo actual
    inordenHelp(nodo->der);   // Visita hijo derecho en in-orden
}

// Realiza el recorrido in-orden sobre el ABB
void tABB::inorden() const {
    inordenHelp(raiz);
    std::cout << std::endl;
}

void tABB::insertarhoja(tipoElem elemento) {

    if (raiz == nullptr) {// Si el árbol está vacío, se crea la raíz
        raiz = new tNodoArbolBin;
        raiz->info = elemento;
        raiz->izq = nullptr;
        raiz->der = nullptr;
        nElems++;
        return;
    }

    // Recorro desde la raiz
    tNodoArbolBin* curr = raiz;
    bool bandera = true;

    while (bandera) {
        if (elemento < curr->info) {
            if (curr->izq != nullptr) {
                curr = curr->izq;
            } else {
                curr->izq = new tNodoArbolBin;
                curr->izq->info = elemento;
                curr->izq->izq = nullptr; // Inicializar en nullptr
                curr->izq->der = nullptr; // Inicializar en nullptr
                bandera = false;
            }
        } else if (elemento > curr->info) { // Evita insertar duplicados idénticos
            if (curr->der != nullptr) {
                curr = curr->der;
            } else {
                curr->der = new tNodoArbolBin;
                curr->der->info = elemento;
                curr->der->izq = nullptr; // Inicializar en nullptr
                curr->der->der = nullptr; // Inicializar en nullptr
                bandera = false;
            }
        } else {
            // El elemento ya existe en el árbol
            return;
        }
    }

    nElems++;
    return;
}