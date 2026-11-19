// Guía C3 · Ejercicio 08
// Retorna la cantidad de componentes conexas de un grafo no dirigido en
// O(V+E). Cada vértice aislado cuenta como una componente. Las marcas vienen
// en NOVISITADO.
// Prepara también la justificación que solicita la guía.

#include <iostream>
#include "tGrafo.hpp"
#include "tCola.hpp"

namespace {
bool pendiente = false;
}

// BFS de apoyo. Marca todos los vértices alcanzables desde s.
void BFS(tGrafo& G, tVertice s) {
    tCola Q;
    G.setMark(s, VISITADO);
    Q.enqueue(s);
    while (Q.size() != 0) {
        tVertice v = Q.frontValue();
        Q.dequeue();
        for (tVertice w = G.first(v); w < G.nVertex(); w = G.next(v,w)) {
            if (G.getMark(w) == NOVISITADO) {
                G.setMark(w,VISITADO);
                Q.enqueue(w);
            }
        }
    }
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
int componentesDesconectadas(tGrafo* G) {
    (void)G;
    pendiente = true;
    return 0;
}

namespace {
int errores = 0;

void estado(bool correcto) {
    if (pendiente) std::cout << "  [PENDIENTE]";
    else std::cout << (correcto ? "  [OK]" : "  [ERROR]");
    if (pendiente || !correcto) ++errores;
    pendiente = false;
    std::cout << '\n';
}
template<class T>
void prueba(const char* nombre, T obtenido, T esperado) {
    std::cout << nombre << '\n' << "  Mi resultado: ";
    if (pendiente) std::cout << "pendiente";
    else std::cout << obtenido;
    std::cout << " | Esperado: " << esperado;
    estado(obtenido == esperado);
}
}

int main() {
    tGrafo g(6,false);
    g.setEdge(0,1,1); g.setEdge(1,2,1); g.setEdge(3,4,1);
    prueba("Dos grupos y un aislado",componentesDesconectadas(&g),3);
    tGrafo vacio(0,false); prueba("Vacío",componentesDesconectadas(&vacio),0);
    return errores == 0 ? 0 : 1;
}
