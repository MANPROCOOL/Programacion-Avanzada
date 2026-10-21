#include <iostream>
#include <initializer_list>
#include "ABB.hpp"

// Tu ABB.hpp llama tNodo al nodo del enunciado. No modifiques el TDA.
typedef tNodo tNodoArbolBin;

/* P16: Recibe la raiz de un ABB y dos elementos diferentes.
   Si ambos existen, retorna un puntero a su ancestro comun mas cercano.
   Si uno es ancestro del otro, retorna ese mismo nodo.
   Convencion de estas pruebas: retorna nullptr si falta algun elemento.
   Objetivo: O(log2(n)) en un ABB balanceado.
   Puedes agregar funciones auxiliares.
*/

bool comprobador(tNodoArbolBin* raiz, tipoElem buscar){

    if (raiz == nullptr){return 0;}
    if (raiz->info == buscar) {return 1;}
    if (buscar < raiz->info){
        return comprobador(raiz->izq, buscar);
    }
    else{
        return comprobador(raiz->der, buscar);
    }

}

tNodoArbolBin* buscaancestro(tNodoArbolBin* raiz, tipoElem a1, tipoElem a2){

    // Hare una busqueda binaria, se ejecutara en paralelo y a cada iteracion me dira el nodo actual
    // Planteare los casos base
    if (raiz == nullptr) {return nullptr;}
    bool separacion = ((raiz->info < a1 && raiz->info > a2) || (raiz->info > a1 && raiz->info < a2)); // aca el camino de la busquda binaria se separa
    bool igual = (raiz->info == a1 || raiz->info == a2); // aca la busqueda encuentra uno de los 2 elementos
    if (separacion || igual) {
        return raiz;
    }
    if (a1 < raiz->info){
        return buscaancestro(raiz->izq, a1, a2);
    }
    else {return buscaancestro(raiz->der, a1, a2);}

}

tNodoArbolBin* ancestroComun(tNodoArbolBin* raiz, tipoElem a1, tipoElem a2) {

    // llamare a comprobar 1 vez por elemento y luego mi comprobador
    if (!comprobador(raiz, a1) || !comprobador(raiz, a2)) {return nullptr;}
    else {return buscaancestro(raiz, a1, a2);}

}

/* Justifica aqui la complejidad de tu solucion (maximo 5 lineas):

 Busqueda binaria con poda tiene complejidad log base 2 de n
 y hago busqueda binaria un par de veces



*/

// ===== PRUEBAS: NO NECESITAS MODIFICAR DESDE AQUI =====
namespace pruebas {
    void insertar(tNodo*& raiz, int valor) {
        if (raiz == nullptr) {
            raiz = new tNodo{valor, nullptr, nullptr};
        } else if (valor < raiz->info) {
            insertar(raiz->izq, valor);
        } else if (valor > raiz->info) {
            insertar(raiz->der, valor);
        }
    }

    void liberar(tNodo* raiz) {
        if (raiz == nullptr) return;
        liberar(raiz->izq);
        liberar(raiz->der);
        delete raiz;
    }

    // Busca por direccion, sin desreferenciar punteros ajenos al arbol.
    bool identificar(tNodo* raiz, tNodo* resultado, int& valor) {
        if (raiz == nullptr) return false;
        if (raiz == resultado) {
            valor = raiz->info;
            return true;
        }
        return identificar(raiz->izq, resultado, valor)
            || identificar(raiz->der, resultado, valor);
    }

    void ejecutar(int numero, const char* descripcion,
                  std::initializer_list<int> valores, int a1, int a2,
                  bool existe, int esperado) {
        tNodo* raiz = nullptr;
        for (int valor : valores) insertar(raiz, valor);
        tNodo* obtenido = ancestroComun(raiz, a1, a2);
        int valorObtenido = 0;
        bool pertenece = identificar(raiz, obtenido, valorObtenido);
        bool correcto = existe ? pertenece && valorObtenido == esperado
                               : obtenido == nullptr;

        std::cout << "Prueba " << numero << ": " << descripcion
                  << "\na1 = " << a1 << ", a2 = " << a2 << '\n';
        std::cout << "Tu resultado: ";
        if (obtenido == nullptr) std::cout << "nullptr";
        else if (pertenece) std::cout << valorObtenido;
        else std::cout << "puntero que no pertenece al arbol";
        std::cout << "\nEsperado:     ";
        if (existe) std::cout << esperado;
        else std::cout << "nullptr";
        std::cout << "\n" << (correcto ? "OK" : "REVISAR") << "\n\n";
        liberar(raiz);
    }
}

int main() {
    // Arbol de la figura 1 del PDF, construido por inserciones en ABB.
    const std::initializer_list<int> ejemplo =
        {15, 7, 25, 3, 10, 20, 29, 4, 9, 12, 26, 34, 8, 13};

    pruebas::ejecutar(1, "Ejemplo del PDF", ejemplo, 8, 13, true, 10);
    pruebas::ejecutar(2, "Distintos lados de la raiz", ejemplo, 4, 26, true, 15);
    pruebas::ejecutar(3, "Ambos en el subarbol derecho", ejemplo, 26, 34, true, 29);
    pruebas::ejecutar(4, "a1 es ancestro de a2", ejemplo, 10, 8, true, 10);
    pruebas::ejecutar(5, "a2 es ancestro de a1", ejemplo, 8, 10, true, 10);
    pruebas::ejecutar(6, "Uno de los elementos es la raiz", ejemplo, 15, 13, true, 15);
    pruebas::ejecutar(7, "Mismos elementos de P1 en orden inverso", ejemplo, 13, 8, true, 10);
    pruebas::ejecutar(8, "Falta a1", ejemplo, 11, 13, false, 0);
    pruebas::ejecutar(9, "Falta a2 en el otro lado de la raiz", ejemplo, 8, 100, false, 0);
    pruebas::ejecutar(10, "Faltan ambos", ejemplo, 11, 100, false, 0);
    pruebas::ejecutar(11, "Arbol vacio", {}, 1, 2, false, 0);
    pruebas::ejecutar(12, "Arbol con un nodo y un elemento ausente", {5}, 5, 6, false, 0);
    pruebas::ejecutar(13, "ABB inclinado", {2, 4, 6, 8, 10}, 4, 10, true, 4);
    return 0;
}
