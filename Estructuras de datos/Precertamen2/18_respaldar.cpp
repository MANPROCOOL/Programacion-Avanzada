#include <iostream>
#include "ABB.hpp" // Reutiliza el struct tNodo de tu TDA existente.

/*
Ejercicio 18, adaptado por peticion a salida en consola.
No se crean archivos de texto.

La funcion respaldar ya coordina las dos lineas:
1. Preorden con profundidad.
2. Inorden con profundidad.

Trabaja SOLO dentro de preOrdenHelp e inOrdenHelp.
El arbol es binario general: no supongas que esta ordenado como un ABB.
Usamos ABB.hpp unicamente porque contiene tu definicion de tNodo:
info (int), izq y der.

Formato de cada elemento: valor (profundidad)
La raiz tiene profundidad 0.
No modificar ni liberar nodos del arbol.
*/
void preOrdenHelp(tNodo* nodo, int profundidad) {

    if (nodo == nullptr) {return;}
    std::cout << nodo->info << " (" << profundidad << ") ";
    preOrdenHelp(nodo->izq, profundidad + 1);
    preOrdenHelp(nodo->der, profundidad + 1);
}

void inOrdenHelp(tNodo* nodo, int profundidad) {

    if (nodo == nullptr) {return;}
    inOrdenHelp(nodo->izq, profundidad + 1);
    std::cout << nodo->info << " (" << profundidad << ") ";
    inOrdenHelp(nodo->der, profundidad + 1);

}

// Coordinacion preparada: no necesitas modificarla.
void respaldar(tNodo* raiz) {
    preOrdenHelp(raiz, 0);
    std::cout << '\n';
    inOrdenHelp(raiz, 0);
    std::cout << '\n';
}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(const char* nombre, tNodo* raiz, const char* preEsperado, const char* inEsperado) {
    std::cout << nombre << "\nTu output (preorden / inorden):\n";
    respaldar(raiz);
    std::cout << "Esperado (preorden / inorden):\n" << preEsperado << '\n' << inEsperado << "\n";
    if (raiz == nullptr)
        std::cout << "(Para el arbol vacio se esperan dos lineas vacias.)\n";
    std::cout << '\n';
}

int main() {
    // 1. Arbol del ejemplo del PDF.
    // Nivel 0: 15
    // Nivel 1: 9 20
    // Nivel 2: 7 12 19 25
    // Nivel 3: 18 (izquierdo de 19), 21 (izquierdo de 25)
    tNodo n7{7, nullptr, nullptr}, n12{12, nullptr, nullptr};
    tNodo n18{18, nullptr, nullptr}, n21{21, nullptr, nullptr};
    tNodo n19{19, &n18, nullptr}, n25{25, &n21, nullptr};
    tNodo n9{9, &n7, &n12}, n20{20, &n19, &n25};
    tNodo n15{15, &n9, &n20};
    probar("1. Ejemplo del enunciado", &n15,
           "15 (0) 9 (1) 7 (2) 12 (2) 20 (1) 19 (2) 18 (3) 25 (2) 21 (3)",
           "7 (2) 9 (1) 12 (2) 15 (0) 18 (3) 19 (2) 20 (1) 21 (3) 25 (2)");

    // Los siguientes son casos propios adicionales.
    tNodo unico{42, nullptr, nullptr};
    probar("2. Solo raiz", &unico, "42 (0)", "42 (0)");

    probar("3. Arbol vacio", nullptr, "", "");

    tNodo c3{3, nullptr, nullptr};
    tNodo c2{2, &c3, nullptr}, c1{1, &c2, nullptr};
    probar("4. Cadena izquierda", &c1,
           "1 (0) 2 (1) 3 (2)", "3 (2) 2 (1) 1 (0)");

    tNodo d3{9, nullptr, nullptr};
    tNodo d2{8, nullptr, &d3}, d1{7, nullptr, &d2};
    probar("5. Cadena derecha", &d1,
           "7 (0) 8 (1) 9 (2)", "7 (0) 8 (1) 9 (2)");

    // Este arbol NO es un ABB.
    tNodo g4{99, nullptr, nullptr};
    tNodo g2{30, nullptr, &g4}, g3{-5, nullptr, nullptr};
    tNodo g1{10, &g2, &g3};
    probar("6. Binario general, no ABB", &g1,
           "10 (0) 30 (1) 99 (2) -5 (1)",
           "30 (1) 99 (2) 10 (0) -5 (1)");
    return 0;
}

