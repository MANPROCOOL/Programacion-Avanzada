#include <iostream>
#include "ABB.hpp"

// Imprimir en orden ascendente los valores del ABB dentro de [x, y].
// Precondiciones del ejercicio: x <= y y x esta presente en el arbol.
// Meta solicitada: O(h + N), con h = profundidad de x y N = valores impresos.
void inordenRango(tNodo* t, int x, int y) {
    if (t == nullptr) return;

    // Solo recorre la izquierda si el nodo actual es mayor que x
    if (t->info > x) {
        inordenRango(t->izq, x, y);
    }

    // Imprime si está dentro del rango [x, y]
    if (x <= t->info && t->info <= y) {
        std::cout << t->info << ' ';
    }

    // Solo recorre la derecha si el nodo actual es menor que y
    if (t->info < y) {
        inordenRango(t->der, x, y);
    }
}

int main() {
    tABB arbol;
    // Ejemplo de ABB del material del curso (diapositiva 58).
    int datos[] = {16, 5, 30, 12, 28, 32, 19, 29, 17, 21};
    for (int dato : datos) arbol.insert(dato);

    // Cada llamada de prueba usa un x presente en el arbol.
    std::cout << "Rango [16, 28]: ";
    inordenRango(arbol.getRaiz(), 16, 28);
    std::cout << "\nEsperado:       16 17 19 21 28\n\n";

    std::cout << "Rango [19, 19]: ";
    inordenRango(arbol.getRaiz(), 19, 19);
    std::cout << "\nEsperado:       19\n\n";

    std::cout << "Rango [5, 100]: ";
    inordenRango(arbol.getRaiz(), 5, 100);
    std::cout << "\nEsperado:       5 12 16 17 19 21 28 29 30 32\n\n";

    std::cout << "Rango [5, 12]:  ";
    inordenRango(arbol.getRaiz(), 5, 12);
    std::cout << "\nEsperado:       5 12\n\n";

        std::cout << "Rango [30, 32]: ";
    inordenRango(arbol.getRaiz(), 30, 32);
    std::cout << "\nEsperado:       30 32\n";
    return 0;
}
