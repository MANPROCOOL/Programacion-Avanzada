#include "nodo.h"
#ifndef PILA_ABB_H
#define PILA_ABB_H
#define MAXSTACK 200001

// ─────────────────────────────────────────────────────────────────────────────
//  Pila para Arbol Binario de Busqueda
//  INF-20325 – Estructuras de Datos  |  UTFSM 2026-2
// ─────────────────────────────────────────────────────────────────────────────

typedef tNodoArbolBin tElemPila;

class tPila {
	private:
	  unsigned int maxSize;  // tamaño maximo de la pila
	  unsigned int top;      // tamaño actual de la pila
	  tElemPila *stackArray; // arreglo con los elementos de la pila

	public:
	  //constructor
	  tPila ();

	  //destructor
	  ~tPila ();

	  //reinicializa la pila
	  void clear ();

	  //inserta un elemento en el tope de la pila
	  int push (tElemPila item);

	  // elimina el elemento que está en el tope de la pila
	  void pop ();

	  // retorna una copia del elemento que está en el tope de la pila
	  tElemPila topValue ();

	  // retorna el tamaño de una pila
	  int size ();
};

#endif