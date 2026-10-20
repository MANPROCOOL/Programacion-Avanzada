#include "nodo.h"
#ifndef ABB_H
#define ABB_H
#include "pila_abb.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Arbol Binario de Busqueda
//  INF-20325 – Estructuras de Datos  |  UTFSM 2026-2
// ─────────────────────────────────────────────────────────────────────────────

class tABB {
    tNodoArbolBin* raiz;
    int nElems;
public:
    tABB();
    // elimina todos los elementos de un ABB, dejándolo vacío
    void clear();
    void clearHelp(tNodoArbolBin *nodo);

	tNodoArbolBin* getRaiz();
	
    // inserta un elemento “item” en el ABB
    void insert(tipoElem item, std::string accion);
    void insertHelp(tNodoArbolBin *&nodo, tipoElem item, std::string accion);

    // elimina un elemento “item” de un ABB
    //void remove(tipoElem item);

    // busca un “item” en un ABB, retorna 0 en caso de no encontrarlo
    int find(tipoElem item);
    int findHelp(tNodoArbolBin *nodo, tipoElem item);

    // cantidad de elementos en el árbol
    int size();

    // recorrido in-orden de un ABB
    void inOrden();
    void inOrdenHelp(tNodoArbolBin *nodo);

    // recorrido post-orden de un ABB
    void postOrden();
	void postOrdenHelp(tNodoArbolBin *nodo);

    // recorrido pre-orden de un ABB
    void preOrden();
	void preOrdenHelp(tNodoArbolBin *nodo);

	// recorrido por anchura
	void porAnchura();
    void porAnchuraHelp(tNodoArbolBin *nodo);
	
	// imprimir arbol
	void verArbol(tNodoArbolBin *nodo, int altura);
	
	// decisiones minimas
	void decisionesMinimas(std::string accion, tipoElem *hoja);
	void decisionesMinimasHelp(tNodoArbolBin *nodo, tPila* camino, std::string accion, tipoElem *hoja, float &minimo);
};

#endif