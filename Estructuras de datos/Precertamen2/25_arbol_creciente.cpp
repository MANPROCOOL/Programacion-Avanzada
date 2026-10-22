#include <cassert>
#include <iostream>
#include <string>

// Pregunta 25: en cada nivel debe haber nivel + 1 nodos.
// La raiz esta en el nivel 0. Los valores no determinan si es creciente.
// Retorna true si cumple. Si no cumple, retorna false y muestra el nivel,
// la cantidad real y la cantidad esperada. Tiempo requerido: O(n).
// Para estas pruebas: reportar el primer nivel que falla.
// Convencion para el caso vacio (no especificado en el enunciado): true.
// Solo se revisan niveles existentes; no hay que exigir un nivel adicional.

struct tNodo {
    unsigned int info;
    tNodo* izq;
    tNodo* der;
};

// Cola local: mismas operaciones que tu cola, pero almacena punteros.
// No requiere modificar tus TDA ni compilar Cola.cpp.
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

bool esCreciente(tNodo* raiz) {

    // Hare un bfs, y tendre 2 contadores que cuenten la cantidad de hijos por nivel
    int actual = 1, siguiente = 0, estable = 1; // mis acumiladores, estable conservara el nivel actual sin variar 
    tColaNodos pendientes;
    if (raiz != nullptr) {pendientes.enqueue(raiz);}
    else {return true;} // convencion impuesta por mi compa gpt

    while (pendientes.size()){
        tNodo* temp = pendientes.frontValue();
        pendientes.dequeue();

        if (temp->izq != nullptr){
            pendientes.enqueue(temp->izq);
            siguiente += 1;
        }
        if (temp->der != nullptr){
            pendientes.enqueue(temp->der);
            siguiente += 1;
        }
        actual -= 1;
        if (actual == 0){ //ya recorri todos los nodos del nivel
            if (siguiente != estable + 1 && siguiente != 0){
                std::cout << "Nivel " << estable << ": tiene " << siguiente << " nodos; deberia tener " << estable + 1 << '\n';
                return 0;
            }
            actual = siguiente;
            siguiente = 0;
            estable += 1;
        }

    }
    return 1;
}

// Pruebas: no necesitas editar desde aqui.
tNodo* nodo(unsigned int valor, tNodo* izq = nullptr, tNodo* der = nullptr) {
    return new tNodo{valor, izq, der};
}

void liberar(tNodo* raiz) {
    if (raiz == nullptr) return;
    liberar(raiz->izq);
    liberar(raiz->der);
    delete raiz;
}

void probar(int numero, const std::string& descripcion, tNodo* raiz,
            bool esperado, const std::string& diagnostico) {
    std::cout << "Caso " << numero << " | " << descripcion << '\n'
              << "Tu diagnostico (si retorna false):\n";
    bool obtenido = esCreciente(raiz);
    std::cout << "Tu retorno:       " << std::boolalpha << obtenido << '\n'
              << "Retorno esperado: " << esperado << '\n'
              << "Diagnostico esperado: " << diagnostico << '\n'
              << (obtenido == esperado ? "Retorno OK" : "REVISAR retorno")
              << "\nCompara tambien el diagnostico de arriba.\n\n";
    liberar(raiz);
}

int main() {
    // Ejemplo del PDF: cantidades por nivel 1, 2, 3, 4.
    probar(1, "Ejemplo del PDF: 1, 2, 3, 4 nodos por nivel",
           nodo(15,
                nodo(9, nodo(21, nodo(23), nodo(35))),
                nodo(20, nodo(18, nodo(19)), nodo(7, nodo(25)))),
           true, "Ninguno");

    probar(2, "Arbol vacio", nullptr, true, "Ninguno");
    probar(3, "Solo raiz", nodo(99), true, "Ninguno");
    probar(4, "Un solo hijo en nivel 1", nodo(10, nodo(20)),
           false, "Nivel 1: tiene 1 nodo; deberia tener 2");
    probar(5, "Dos niveles completos", nodo(8, nodo(100), nodo(1)),
           true, "Ninguno");
    probar(6, "Nivel 2 con pocos nodos",
           nodo(1, nodo(2, nodo(4)), nodo(3, nullptr, nodo(5))),
           false, "Nivel 2: tiene 2 nodos; deberia tener 3");
    probar(7, "Nivel 2 con demasiados nodos",
           nodo(1, nodo(2, nodo(4), nodo(5)), nodo(3, nodo(6), nodo(7))),
           false, "Nivel 2: tiene 4 nodos; deberia tener 3");
    probar(8, "Tres niveles crecientes; valores repetidos",
           nodo(0, nodo(0, nodo(0), nodo(0)), nodo(0, nodo(0))),
           true, "Ninguno");
    probar(9, "Falla en nivel 3 despues de 1, 2, 3",
           nodo(1, nodo(2, nodo(4, nodo(7)), nodo(5)), nodo(3, nodo(6))),
           false, "Nivel 3: tiene 1 nodo; deberia tener 4");
    return 0;
}
