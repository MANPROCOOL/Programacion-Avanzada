#include "abb.h"
#include "cola_abb.cpp"
#include "pila_abb.cpp"
#include <iostream>

tABB::tABB(){
    raiz = nullptr;
    nElems = 0;
};

// elimina todos los elementos de un ABB T, dejándolo vacío
void tABB::clear() {
    clearHelp(raiz); // función auxiliar para eliminar los nodos
    raiz = nullptr;
    nElems = 0;
}

// función auxiliar recursiva para eliminar los nodos del árbol
void tABB::clearHelp(tNodoArbolBin *nodo) {
    if (nodo == nullptr) // árbol vacío, se detiene
        return;
    clearHelp(nodo->izq); // visita subárbol izquierdo recursivamente
    clearHelp(nodo->der); // visita subárbol derecho recursivamente
    delete nodo; // después de borrar subárboles, se borra a sí mismo
}

tNodoArbolBin* tABB::getRaiz() { return raiz; }

void tABB::insert(tipoElem item, std::string accion){
    if (!find(item)){
        insertHelp(raiz, item, accion);
    }
    return;
}

void tABB::insertHelp(tNodoArbolBin *&nodo, tipoElem item, std::string accion){
    if (nodo == nullptr){
        nodo = new tNodoArbolBin;
        nodo->info = item;
		nodo->accion = accion;
        nodo->izq = nullptr;
        nodo->der = nullptr;
        nElems++;
    }
    else{
        if (item < nodo->info){
            insertHelp(nodo->izq, item, accion);
        }
        else
            insertHelp(nodo->der, item, accion);
    }
    return;
}

// busca un "item" en un ABB, retorna 0 en caso de no encontrarlo
int tABB::find(tipoElem item) {
    return findHelp(raiz, item);
}

int tABB::findHelp(tNodoArbolBin *nodo, tipoElem item) {
    if (nodo == nullptr)
        return 0; // item no está en el ABB
    if (nodo->info == item)
        return 1; // item encontrado
    if (item < nodo->info)
        return findHelp(nodo->izq, item);
    else
        return findHelp(nodo->der, item);
}

// cantidad de elementos en el árbol
int tABB::size() { return nElems; }

// recorrido in-orden de un ABB 
void tABB::inOrden () {
    inOrdenHelp (raiz);
    std::cout << std::endl;
}

void tABB::inOrdenHelp (tNodoArbolBin *nodo) {
    //std::cout << "en el inOrder " << " ";
	if (nodo == nullptr) return;
    inOrdenHelp (nodo->izq); // visita hijo izquierdo en in-orden
    std::cout << nodo->info << " "; // procesa nodo actual
    inOrdenHelp (nodo->der); // visita hijo derecho en in-orden
}

// recorrido post-orden de un ABB
void tABB::postOrden() {
    postOrdenHelp (raiz);
    std::cout << std::endl;
}

void tABB::postOrdenHelp(tNodoArbolBin *nodo) {
    //std::cout << "en el inOrder " << " ";
	if (nodo == nullptr) return;
    postOrdenHelp (nodo->izq); // visita hijo izquierdo en in-orden
    postOrdenHelp (nodo->der); // visita hijo derecho en in-orden
    std::cout << nodo->info << " "; // procesa nodo actual
}

// recorrido post-orden de un ABB
void tABB::preOrden() {
    preOrdenHelp (raiz);
    std::cout << std::endl;
}

void tABB::preOrdenHelp(tNodoArbolBin *nodo) {
    //std::cout << "en el inOrder " << " ";
	if (nodo == nullptr) return;
    std::cout << nodo->info << " "; // procesa nodo actual
    preOrdenHelp (nodo->izq); // visita hijo izquierdo en in-orden
    preOrdenHelp (nodo->der); // visita hijo derecho en in-orden
}

// recorrido por anchura
void tABB::porAnchura() {
    porAnchuraHelp(raiz);
    std::cout << std::endl;
}

void tABB::porAnchuraHelp(tNodoArbolBin* nodo) {
    if (nodo == nullptr) return;
	
	tCola cola;
	cola.enqueue(*raiz);

    while (!(cola.size()==0)) {
        tElemCola actual = cola.frontValue();
        cola.dequeue();
        std::cout << actual.info << " ";
        if (actual.izq != nullptr) cola.enqueue(*(actual.izq));
        if (actual.der != nullptr) cola.enqueue(*actual.der);
    }
}

// imprimir arbol
void tABB::verArbol(tNodoArbolBin *nodo, int altura) {
	if(nodo==nullptr) return;
	
	verArbol(nodo->der, altura+1);
	for(int i=0; i<altura; i++) std::cout<<" ";
	std::cout << nodo->info << "\n";
	verArbol(nodo->izq, altura+1);
}

// decisiones minimas
void tABB::decisionesMinimas(std::string accion, tipoElem *hoja) {
	tPila* camino = new tPila;
	float minimo = 9999999999;
	
	decisionesMinimasHelp(raiz, camino, accion, hoja, minimo);
}
void tABB::decisionesMinimasHelp(tNodoArbolBin *nodo, tPila* camino, std::string accion, tipoElem *hoja, float &minimo) {
	
    if (nodo == nullptr){return;}
    camino->push(*nodo);
    if (nodo->accion == accion && minimo > camino->size() - 1 && nodo->izq == nullptr && nodo->der == nullptr) { 
        *hoja = nodo->info;      // Si lo encontre y ademas es mejor candidato, retorno
        minimo = camino->size() - 1;
    }
    else { // Si no lo encontre, sigo buscando
        decisionesMinimasHelp(nodo->izq, camino, accion, hoja, minimo);
        decisionesMinimasHelp(nodo->der, camino, accion, hoja, minimo);
    }
    camino->pop();
}	