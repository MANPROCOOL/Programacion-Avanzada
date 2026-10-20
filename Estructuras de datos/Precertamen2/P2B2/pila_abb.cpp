#include "pila_abb.h"

tPila::tPila(){
  maxSize = MAXSTACK;
  top = 0;
  stackArray = new tElemPila[maxSize];
}

tPila::~tPila(){
  delete[] stackArray;
  //std::cout << "destructor invocado" << std::endl;
}

//reinicializa la pila
void tPila::clear (){
  top = 0; 
}

//inserta un elemento en el tope de la pila
int tPila::push (tElemPila item){
  if (top == maxSize) return 0;
  stackArray[top++] = item;
  return 1; // inserción exitosa
}

// elimina el elemento que está en el tope de la pila
void tPila::pop (){
  if( top > 0 ){
    top--;
  } 
}

// retorna una copia del elemento que está en el tope de la pila
tElemPila tPila::topValue (){
  if( top <= 0 ) {tElemPila vacio; return vacio;}
  return stackArray[top-1];
}

// retorna el tamaño de una pila
int tPila::size (){
  return top; 
}
