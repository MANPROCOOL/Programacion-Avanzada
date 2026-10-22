#include <cassert>
#include <initializer_list>
#include <iostream>
#include <string>

// Pregunta 27: Josephus.
// Contar comienza en el frente como 1. Se elimina al k-esimo y se
// continua contando desde la persona siguiente hasta quedar una sola.
// Ejemplo: [A, B, C, D, E], k = 2 -> sobrevive C.
// Precondiciones del ejercicio: cola no vacia y k >= 1.
// La funcion puede modificar la cola y retorna el nombre sobreviviente.
//
// Tu Cola.hpp guarda int. Esta version local guarda nombres, conserva
// sus operaciones y no requiere modificar ni compilar tus otros TDA.
typedef std::string tElemCola;

class tCola {
private:
    struct tNodo {
        tElemCola info;
        tNodo* sig;
    };
    tNodo* frente;
    tNodo* fin;
    int tam;

public:
    tCola() : frente(nullptr), fin(nullptr), tam(0) {}
    ~tCola() { clear(); }
    tCola(const tCola&) = delete;
    tCola& operator=(const tCola&) = delete;

    int enqueue(tElemCola item) {
        tNodo* nuevo = new tNodo{item, nullptr};
        if (tam == 0) frente = nuevo;
        else fin->sig = nuevo;
        fin = nuevo;
        ++tam;
        return 1;
    }

    void dequeue() {
        assert(tam > 0);
        tNodo* aux = frente;
        frente = frente->sig;
        delete aux;
        --tam;
        if (tam == 0) fin = nullptr;
    }

    tElemCola frontValue() const {
        assert(tam > 0);
        return frente->info;
    }

    int size() const { return tam; }
    void clear() {
        while (tam > 0) dequeue();
    }
};

std::string sobreviviente(tCola& q, int k) {

    // basicamente tengo que ir rotando k - 1 veces
    // luego desencolar, repetir hasta que quede 1 elemento
    while (q.size() - 1){
        for (int i = 1; i < k; i++){
            q.enqueue(q.frontValue());
            q.dequeue();
        }
    q.dequeue();
    }
    return q.frontValue();
}

// Pruebas: no necesitas editar desde aqui.
void probar(int numero, std::initializer_list<std::string> nombres,
            int k, const std::string& esperado) {
    tCola q;
    std::cout << "Caso " << numero << " | Cola: [";
    bool primero = true;
    for (const std::string& nombre : nombres) {
        if (!primero) std::cout << ", ";
        std::cout << nombre;
        primero = false;
        q.enqueue(nombre);
    }
    std::cout << "] | k = " << k << '\n';
    const std::string obtenido = sobreviviente(q, k);
    std::cout << "Tu resultado: " << obtenido << '\n'
              << "Esperado:     " << esperado << '\n'
              << (obtenido == esperado ? "OK" : "REVISAR") << "\n\n";
}

int main() {
    probar(1, {"A", "B", "C", "D", "E"}, 2, "C");
    probar(2, {"A", "B", "C", "D", "E"}, 1, "E");
    probar(3, {"A", "B", "C", "D", "E"}, 3, "D");
    probar(4, {"A", "B", "C", "D", "E"}, 5, "B");
    probar(5, {"A", "B", "C", "D", "E"}, 7, "D");
    probar(6, {"Pepe"}, 1, "Pepe");
    probar(7, {"Pepe"}, 12, "Pepe");
    probar(8, {"Ana", "Luis"}, 2, "Ana");
    probar(9, {"Ana", "Luis"}, 3, "Luis");
    probar(10, {"Ana", "Beto", "Caro", "Diego", "Eva", "Fran", "Gabi"},
           3, "Diego");
    probar(11, {"P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9", "P10"},
           4, "P5");
    return 0;
}
