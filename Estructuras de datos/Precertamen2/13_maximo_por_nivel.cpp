#include <cassert>
#include <iostream>

// Struct exacto de la pregunta 13. info es unsigned int.
// No incluir ABB.hpp aqui: ya contiene otro struct tNodo con info int.
struct tNodo {
    unsigned int info;
    tNodo* izq;
    tNodo* der;
};

// Tu cola original almacena enteros. Esta cola adicional permite
// guardar tNodo* y conserva sus nombres de operaciones.
// No modifica tus TDA ni elimina los nodos del arbol.
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
Pregunta 13: maximoPorNivel.
- Imprimir el mayor elemento de cada nivel, desde la raiz hacia abajo.
- Es un arbol binario GENERAL; no se puede suponer que sea ABB.
- Tiempo requerido: O(n), n = cantidad de nodos.
- No modificar ni liberar los nodos del arbol.
- Para el caso adicional de arbol vacio, no imprimir elementos.

TDA disponible: tColaNodos, definido arriba en este mismo archivo.
    enqueue(tNodo*)    : agrega un puntero al final.
    frontValue()      : consulta el puntero del frente sin eliminarlo.
    dequeue()         : elimina el frente, no retorna un valor.
    size()            : cantidad actual de elementos.
    clear()           : vacia la cola sin liberar nodos del arbol.
Consultar y eliminar requiere size() > 0.
*/
void maximoPorNivel(tNodo* raiz) {

    // tengo que hacer un recorrido de tipo BFS
    // por cada nivel tengo que encontrar el maximo e imprimirlo
    // el arbol recibido no es un ABB, no cumple la regla de ordenamiento
    tColaNodos pendientes; // la usare para el bfs
    int nivel = 1, sig = 0; //cantidad de nodos por lvl, el actual y el sgt
    if (raiz != nullptr) {
        pendientes.enqueue(raiz); // guardo la raiz en la cola
    }
    unsigned max = 0;
    while(pendientes.size()){
        tNodo* aux = pendientes.frontValue();
        pendientes.dequeue(); // Saco el nodo pendiente de la cola
        if (aux->info > max) {max = aux->info;}
        if (aux->izq != nullptr){ // verifico si existe izq y lo encolo
            pendientes.enqueue(aux->izq);
            sig += 1;
        }
        if (aux->der != nullptr){ // lo mismo con der
            pendientes.enqueue(aux->der);
            sig += 1;
        }
        nivel -= 1;
        if (nivel == 0){
            std::cout << max << ' ';
            max = 0;
            nivel = sig;
            sig = 0; // vuelvo a setear la cantidad de hijos por nivel en 0
        }
    }
    
}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(const char* nombre, tNodo* raiz, const char* esperado) {
    std::cout << nombre << "\nTu output: ";
    maximoPorNivel(raiz);
    std::cout << "\nEsperado:  " << esperado << "\n\n";
}

int main() {
    // 1. Arbol del ejemplo del PDF (no es un ABB).
    // 15: hijos 9 y 20.
    // 9: hijo izquierdo 21.
    // 20: hijos 18 y 7.
    // 18: hijo izquierdo 19. 7: hijo izquierdo 25.
    tNodo n19{19, nullptr, nullptr}, n25{25, nullptr, nullptr};
    tNodo n21{21, nullptr, nullptr};
    tNodo n18{18, &n19, nullptr}, n7{7, &n25, nullptr};
    tNodo n9{9, &n21, nullptr}, n20{20, &n18, &n7};
    tNodo n15{15, &n9, &n20};
    probar("1. Ejemplo del enunciado", &n15, "15 20 21 25");

    // Casos adicionales propios.
    tNodo unico{42, nullptr, nullptr};
    probar("2. Solo raiz", &unico, "42");
    probar("3. Arbol vacio", nullptr, "(sin elementos)");

    // El maximo debe corresponder a cada nivel, no al acumulado global.
    tNodo r2{2, nullptr, nullptr}, r3{3, nullptr, nullptr};
    tNodo r80{80, &r2, nullptr}, r70{70, nullptr, &r3};
    tNodo r100{100, &r80, &r70};
    probar("4. Maximos decrecientes", &r100, "100 80 3");

    tNodo c2{2, nullptr, nullptr};
    tNodo c4{4, nullptr, &c2}, c8{8, nullptr, &c4};
    probar("5. Cadena derecha", &c8, "8 4 2");

    tNodo z1{0, nullptr, nullptr}, z2{0, nullptr, nullptr};
    tNodo z0{0, &z1, &z2};
    probar("6. Valores cero y repetidos", &z0, "0 0");

    tNodo b2{2, nullptr, nullptr}, b4{4, nullptr, nullptr};
    tNodo b20{20, nullptr, nullptr}, b5{5, nullptr, nullptr};
    tNodo b9{9, &b2, &b4}, b3{3, &b20, &b5};
    tNodo b1{1, &b9, &b3};
    probar("7. Maximos en distintas ramas", &b1, "1 9 20");
    return 0;
}
