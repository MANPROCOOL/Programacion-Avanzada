#include <iostream>
#include <initializer_list>
#include "ABB.hpp"
#include "Pila.hpp"
#include "Cola.hpp"

// Usa el nodo de tu ABB, sin definir otro struct.
using tNodoArbolBin = tNodo;

/*
Precondiciones:
- a y b pertenecen al arbol.
- a < raiz->info < b.

Resultado:
- Retornar un arreglo creado con new[].
- Guardar su cantidad de elementos en cantidad.
- Seguir el recorrido a -> raiz -> b.
- Incluir la raiz una sola vez.
- No modificar el arbol.
*/
tipoElem* mergeBranches(tNodoArbolBin* raiz, tipoElem a, tipoElem b, int& cantidad) {

    // primero debo encontrar el camino a cada elemento y guardarlo
    tPila auxcama;
    tCola auxcamb;
    // es un arbol binario de busqueda, puedo hacerlo iterativo
    tNodoArbolBin* tempa = raiz->izq; // a siempre es menor que r
    tNodoArbolBin* tempb = raiz->der; // b siempre es mayor que r
    auxcama.push(tempa->info);
    auxcamb.enqueue(tempb->info);
    while (tempa != nullptr && tempa->info != a){ 
        if (tempa->info < a){
            tempa = tempa->der;
        }
        else if (tempa->info > a){
            tempa = tempa->izq;
        }
        auxcama.push(tempa->info);
    }
    // ya encontre a y guarde su camino en una pila
    // ahora quiero guardar el camino hacia b en una cola
   while (tempb != nullptr && tempb->info != b){ 
        if (tempb->info < b){
            tempb = tempb->der;
        }
        else if (tempb->info > b){
            tempb = tempb->izq;
        }
        auxcamb.enqueue(tempb->info);
    }
    // ya tengo el camino a en una pila y el b en una cola, creo
    // ahora tengo que crear un arreglo para chantar todo
    tipoElem* resultado = new tipoElem[auxcama.size() + auxcamb.size() + 1]; // ese + 1 es por la r
    int i = 0;
    while (auxcama.size()){
        resultado[i] = auxcama.topValue();
        auxcama.pop(), i += 1;
    }
    resultado[i] = raiz->info, i += 1;
    while (auxcamb.size()){
        resultado[i] = auxcamb.frontValue();
        auxcamb.dequeue(), i += 1;
    }
    cantidad = i;
    return resultado;
}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(tABB& arbol, tipoElem a, tipoElem b,
            std::initializer_list<tipoElem> esperado) {
    int cantidad = 0;
    tipoElem* resultado =
        mergeBranches(arbol.getRaiz(), a, b, cantidad);

    std::cout << "Caso a = " << a << ", b = " << b << '\n';
    std::cout << "Tu output: ";

    if (resultado == nullptr) {
        std::cout << "PENDIENTE";
    } else {
        for (int i = 0; i < cantidad; i++) {
            std::cout << resultado[i] << ' ';
        }
    }

    std::cout << "\nEsperado:  ";
    for (tipoElem valor : esperado) {
        std::cout << valor << ' ';
    }
    std::cout << "\n\n";

    delete[] resultado;
}

int main() {
    tABB arbol;

    // La insercion sigue este orden para fijar la forma del ABB.
    for (tipoElem valor :
         {50, 30, 70, 20, 40, 60, 80, 35, 45, 55, 65}) {
        arbol.insert(valor);
    }

    probar(arbol, 30, 70, {30, 50, 70});
    probar(arbol, 20, 80, {20, 30, 50, 70, 80});
    probar(arbol, 35, 65, {35, 40, 30, 50, 70, 60, 65});
    probar(arbol, 45, 55, {45, 40, 30, 50, 70, 60, 55});

    return 0;
}