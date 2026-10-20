#include "nodo.h"
#ifndef COLA_ABB_H
#define COLA_ABB_H
#define MAXQUEUE 200001

// ─────────────────────────────────────────────────────────────────────────────
//  Cola para Arbol Binario de Busqueda
//  INF-20325 – Estructuras de Datos  |  UTFSM 2026-2
// ─────────────────────────────────────────────────────────────────────────────

typedef tNodoArbolBin tElemCola;

class tCola {
  unsigned int maxSize; // tamaño maximo de la cola
  unsigned int first;   // primer elemento de la cola
  unsigned int length;  // tamaño de la cola

  tElemCola *queueArray; // arreglo con los elementos de la pila

public:
  //constructor
  tCola ();

  //destructor
  ~tCola ();

  //reinicializa la cola
  void clear ();
  // inserta un elemento al final de la cola
  int enqueue (tElemCola item);
  // elimina el elemento que está en el frente cola
  void dequeue ();
  // retorna una copia del elemento que está en el frente de la cola
  tElemCola frontValue ();
  // retorna el tamaño de una cola
  int size ();

};

#endif