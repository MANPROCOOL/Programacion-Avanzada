#include <cassert>
#include <iostream>
#include <string>
#include <initializer_list>

// Pregunta 28: retornar una lista con los niveles que impiden que el
// arbol sea lleno. Tiempo requerido: O(n).
// Convencion de las pruebas: raiz en nivel 0; se listan en orden ascendente
// los niveles existentes con menos de 2^nivel nodos. No se consideran
// niveles posteriores al ultimo. El arbol vacio devuelve una lista vacia.
// Un arbol lleno tiene dos hijos en cada nodo interno y todas sus hojas
// en el mismo nivel.
// Los TDA necesarios son locales: no modifiques ni compiles tus otros TDA.

struct tNodo {
    int info;
    tNodo* izq;
    tNodo* der;
};

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
    ~tColaNodos() { while (size()) dequeue(); }
    tColaNodos(const tColaNodos&) = delete;
    tColaNodos& operator=(const tColaNodos&) = delete;

    int enqueue(tNodo* item) {
        Enlace* nuevo = new Enlace{item, nullptr};
        if (tam == 0) frente = nuevo;
        else fin->sig = nuevo;
        fin = nuevo;
        ++tam;
        return 1;
    }
    void dequeue() {
        assert(tam > 0);
        Enlace* aux = frente;
        frente = frente->sig;
        delete aux;
        --tam;
        if (tam == 0) fin = nullptr;
    }
    tNodo* frontValue() const {
        assert(tam > 0);
        return frente->info;
    }
    int size() const { return tam; }
};

// Lista de enteros con cursor; permite retornar por valor sin compartir nodos.
class tLista {
private:
    struct Enlace {
        int info;
        Enlace* sig;
    };
    Enlace* cabeza;
    Enlace* fin;
    Enlace* cursor;
    int tam;
    int posicion;
public:
    tLista() : cabeza(nullptr), fin(nullptr), cursor(nullptr), tam(0), posicion(0) {}
    ~tLista() { clear(); }
    tLista(const tLista& otra) : tLista() {
        for (Enlace* p = otra.cabeza; p != nullptr; p = p->sig) append(p->info);
        moveToPos(otra.posicion);
    }
    tLista& operator=(const tLista& otra) {
        if (this != &otra) {
            clear();
            for (Enlace* p = otra.cabeza; p != nullptr; p = p->sig) append(p->info);
            moveToPos(otra.posicion);
        }
        return *this;
    }
    void clear() {
        while (cabeza != nullptr) {
            Enlace* aux = cabeza;
            cabeza = cabeza->sig;
            delete aux;
        }
        fin = cursor = nullptr;
        tam = posicion = 0;
    }
    void append(int item) {
        Enlace* nuevo = new Enlace{item, nullptr};
        if (fin != nullptr) fin->sig = nuevo;
        else cabeza = nuevo;
        if (posicion == tam) cursor = nuevo;
        fin = nuevo;
        ++tam;
    }
    int length() const { return tam; }
    int currPos() const { return posicion; }
    void moveToStart() { cursor = cabeza; posicion = 0; }
    void moveToEnd() { cursor = nullptr; posicion = tam; }
    void next() {
        if (posicion < tam) { cursor = cursor->sig; ++posicion; }
    }
    void moveToPos(int pos) {
        assert(pos >= 0 && pos <= tam);
        moveToStart();
        while (posicion < pos) next();
    }
    int getValue() const {
        assert(cursor != nullptr);
        return cursor->info;
    }
};

tLista esNoLleno(tNodo* raiz) {
    tLista resultado;
    // ===== INICIO DE TU TRABAJO =====

    // Implementa aqui. Puedes agregar funciones auxiliares.
    // Borra esta linea al implementar tu solucion.
    (void)raiz;

    // ===== FIN DE TU TRABAJO =====
    return resultado;
}

// Pruebas: no necesitas editar desde aqui.
tNodo* nodo(int valor, tNodo* izq = nullptr, tNodo* der = nullptr) {
    return new tNodo{valor, izq, der};
}
void liberar(tNodo* raiz) {
    if (raiz == nullptr) return;
    liberar(raiz->izq);
    liberar(raiz->der);
    delete raiz;
}
void mostrar(tLista& lista) {
    std::cout << '[';
    for (lista.moveToStart(); lista.currPos() < lista.length(); lista.next()) {
        if (lista.currPos() != 0) std::cout << ", ";
        std::cout << lista.getValue();
    }
    std::cout << ']';
}
void probar(int numero, const std::string& descripcion, tNodo* raiz,
            std::initializer_list<int> niveles) {
    tLista esperado;
    for (int nivel : niveles) esperado.append(nivel);
    tLista obtenido = esNoLleno(raiz);
    bool iguales = obtenido.length() == esperado.length();
    obtenido.moveToStart();
    esperado.moveToStart();
    while (iguales && obtenido.currPos() < obtenido.length()) {
        iguales = obtenido.getValue() == esperado.getValue();
        obtenido.next();
        esperado.next();
    }
    std::cout << "Caso " << numero << " | " << descripcion << '\n'
              << "Tu resultado: ";
    mostrar(obtenido);
    std::cout << "\nEsperado:     ";
    mostrar(esperado);
    std::cout << '\n' << (iguales ? "OK" : "REVISAR") << "\n\n";
    liberar(raiz);
}
int main() {
    probar(1, "Arbol vacio", nullptr, {});
    probar(2, "Solo raiz", nodo(1), {});
    probar(3, "Lleno de dos niveles", nodo(1, nodo(2), nodo(3)), {});
    probar(4, "Lleno de tres niveles",
           nodo(1, nodo(2, nodo(4), nodo(5)), nodo(3, nodo(6), nodo(7))), {});
    probar(5, "Solo hijo izquierdo", nodo(1, nodo(2)), {1});
    probar(6, "Solo hijo derecho", nodo(1, nullptr, nodo(2)), {1});
    probar(7, "Cadena: cantidades 1, 1, 1, 1",
           nodo(1, nodo(2, nodo(3, nodo(4)))), {1, 2, 3});
    probar(8, "Un nodo faltante en nivel 2",
           nodo(1, nodo(2, nodo(4), nodo(5)), nodo(3, nodo(6))), {2});
    probar(9, "Nodos internos con dos hijos, hojas a distinta profundidad",
           nodo(1, nodo(2, nodo(4), nodo(5)), nodo(3)), {2});
    probar(10, "Fallan niveles 2 y 3",
           nodo(1, nodo(2, nodo(4, nodo(7)), nodo(5)), nodo(3, nodo(6))), {2, 3});
    probar(11, "Nivel 2 lleno, nivel 3 incompleto",
           nodo(1, nodo(2, nodo(4, nodo(8), nodo(9)), nodo(5)),
                   nodo(3, nodo(6), nodo(7))), {3});
    probar(12, "Valores repetidos: no es necesario que sea ABB",
           nodo(5, nodo(5, nodo(5), nodo(5)), nodo(5, nodo(5), nodo(5))), {});
    return 0;
}
