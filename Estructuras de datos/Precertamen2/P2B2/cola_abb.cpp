#include "cola_abb.h"

//constructor
tCola::tCola (){
  maxSize = MAXQUEUE;
  first = 0;
  length = 0;
  queueArray = new tElemCola[maxSize];
}

// destructor
tCola::~tCola (){
  delete[] queueArray;
}

//reinicializa la cola
void tCola::clear (){
  first = 0;
  length = 0;
}

// inserta un elemento al final de la cola
int tCola::enqueue (tElemCola item){
  if( length == maxSize ) return 0; //no se pudo insertar
  queueArray[ (first+length)%maxSize ] = item;
  length++;
  return 1;
}

// elimina el elemento que está en el frente cola
void tCola::dequeue (){
  if( length == 0 ) return;
  first = (first + 1)%maxSize;
  length--;
}

// retorna una copia del elemento que está en el frente de la cola
tElemCola tCola::frontValue (){
  if( length == 0 ) {tElemCola vacio; return vacio;}
  return queueArray[first];
}

// retorna el tamaño de una cola
int tCola::size (){
  return length;
}
