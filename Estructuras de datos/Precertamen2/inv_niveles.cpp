#include <iostream>
#include <cassert>
#include "ABB.hpp"
#include "Pila.hpp"

// Cola de punteros para este ejercicio. No modifica tus TDA.
// Conserva los nombres de las operaciones de tu tCola.
// Libera sus enlaces, pero nunca los nodos del arbol.
class tColaNodos {
private:
    struct Enlace {
        tNodo* info;
        Enlace* sig;
    };
    Enlace* frente;
    Enlace* fin;
    int tam;

public:
    tColaNodos() : frente(nullptr), fin(nullptr), tam(0) {}
    ~tColaNodos() { clear(); }
    tColaNodos(const tColaNodos&) = delete;
    tColaNodos& operator=(const tColaNodos&) = delete;

    int enqueue(tNodo* item) {
        Enlace* nuevo = new Enlace{item, nullptr};
        if (tam == 0) frente = nuevo;
        else fin->sig = nuevo;
        fin = nuevo;
        tam++;
        return 1;
    }

    tNodo* frontValue() const {
        assert(tam > 0);
        return frente->info;
    }

    void dequeue() {
        assert(tam > 0);
        Enlace* borrar = frente;
        frente = frente->sig;
        delete borrar;
        tam--;
        if (tam == 0) fin = nullptr;
    }

    int size() const { return tam; }

    void clear() {
        while (tam > 0) dequeue();
    }
};

/*
Imprimir los niveles desde el mas profundo hasta la raiz.
Dentro de CADA nivel, mantener el orden de izquierda a derecha.
Es un arbol binario general: no se supone que sea ABB.
No modificar el arbol.

TDA disponibles:
- tPila: TU pila original de enteros, desde Pila.hpp y Pila.cpp.
  push recibe un int; topValue devuelve un int; pop no retorna.
  Para guardar el valor de un nodo, usa su campo info.
- tColaNodos: cola de punteros definida en este mismo archivo.
  enqueue recibe un tNodo*; frontValue devuelve un tNodo*;
  dequeue elimina sin retornar.
Ambas tienen size() y clear(). Consultar o eliminar exige size() > 0.
No modifiques los typedef de tus TDA. El struct tNodo viene de ABB.hpp.
*/
void invNiveles(tNodo* raiz) { // clasico recorrido a lo ancho, como en mate discretas

    tPila salida;             // Guarda valores enteros.
    tColaNodos pendientes;

    if (raiz != nullptr) {
        pendientes.enqueue(raiz);
        salida.push(raiz->info); // pusheo la raiz, que sera la ultima en imprimirse
    }

    while (pendientes.size() > 0) {
        tNodo* actual = pendientes.frontValue();
        pendientes.dequeue();

        // Aquí procesas el nodo actual.

        if (actual->der != nullptr) {
            pendientes.enqueue(actual->der);
            salida.push(actual->der->info);
        }
        if (actual->izq != nullptr) {
            pendientes.enqueue(actual->izq);
            salida.push(actual->izq->info);
        }
    }
    while (salida.size()){
        std::cout << salida.topValue() << ' ';
        salida.pop();
    }

}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(const char* nombre, tNodo* raiz, const char* esperado) {
    std::cout << nombre << "\nTu output: ";
    invNiveles(raiz);
    std::cout << "\nEsperado:  " << esperado << "\n\n";
}

int main() {
    probar("1. Arbol vacio", nullptr, "(sin elementos)");

    tNodo unico{42, nullptr, nullptr};
    probar("2. Solo raiz", &unico, "42");

    // Nivel 0: 1
    // Nivel 1: 2 3
    // Nivel 2: 4 5 6 7
    tNodo n4{4, nullptr, nullptr}, n5{5, nullptr, nullptr};
    tNodo n6{6, nullptr, nullptr}, n7{7, nullptr, nullptr};
    tNodo n2{2, &n4, &n5}, n3{3, &n6, &n7};
    tNodo n1{1, &n2, &n3};
    probar("3. Completo: verificar izquierda a derecha", &n1,
           "4 5 6 7 2 3 1");

    // Nivel 0: 10
    // Nivel 1: 20 30
    // Nivel 2: 40 50
    // Nivel 3: 60
    tNodo i60{60, nullptr, nullptr};
    tNodo i40{40, nullptr, &i60}, i50{50, nullptr, nullptr};
    tNodo i20{20, nullptr, &i40}, i30{30, &i50, nullptr};
    tNodo i10{10, &i20, &i30};
    probar("4. Irregular: hojas en distintas profundidades", &i10,
           "60 40 50 20 30 10");

    tNodo c3{3, nullptr, nullptr};
    tNodo c2{2, &c3, nullptr}, c1{1, &c2, nullptr};
    probar("5. Cadena izquierda", &c1, "3 2 1");

    tNodo d3{9, nullptr, nullptr};
    tNodo d2{8, nullptr, &d3}, d1{7, nullptr, &d2};
    probar("6. Cadena derecha", &d1, "9 8 7");

    tNodo r2{5, nullptr, nullptr}, r3{5, nullptr, nullptr};
    tNodo r1{5, &r2, &r3};
    probar("7. Valores repetidos", &r1, "5 5 5");
}