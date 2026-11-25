// Guía C3 · Ejercicio 06
// Grafo no dirigido con al menos una ruta. Retorna el mínimo de rutas nuevas
// para que cada ciudad tenga acceso a alguna otra. Una componente con dos o
// más ciudades ya cumple esa condición. Complejidad O(n+m).
// Prepara también la justificación que solicita la guía.

#include <iostream>
#include "tGrafo.hpp"

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
int minimaCantRutas(tGrafo& G) {

    int n = G.nVertex();
    if (n <= 1){return 0;}
    int rutas = 0;
    tVertice pendiente = n;

    for (tVertice v = 0; v < n; v++) {
        tVertice w = G.first(v);
        if (w == v)
            w = G.next(v, w);  // Ignora un lazo hacia sí misma.

        if (w < n) // si el nodo si tiene vecinos, no me interesa
            continue;

        if (pendiente == n) { // si encontre un nodo solo, pero no hay otro nodo solo pendiente
            pendiente = v; // declaro ese nodo como pendiente
        } else {
            G.setEdge(pendiente, v, 1); // encontre 2 nodos solos, los conecto entre si
            rutas++;
            pendiente = n; // borro el nodo que tenia pendiente
        }
    }

    if (pendiente < n) { // si me quedo un nodo pendiente
        tVertice otra = 0; // lo tratare de conectar con el nodo 0
        if (pendiente == 0) // y si el nodo 0 es el unico que esta aislado?
            otra = 1; // lo conecto con otro nodo que exista

        G.setEdge(pendiente, otra, 1);
        rutas++;
    }

    return rutas;
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
    tGrafo gTres(5, false);
    gTres.setEdge(0, 1, 1);
    prueba("Tres aisladas", minimaCantRutas(gTres), 2);

    tGrafo gUna(5, false);
    gUna.setEdge(0, 1, 1);
    gUna.setEdge(2, 3, 1);
    prueba("Una aislada", minimaCantRutas(gUna), 1);

    tGrafo gDosComponentes(5, false);
    gDosComponentes.setEdge(0, 1, 1);
    gDosComponentes.setEdge(2, 3, 1);
    gDosComponentes.setEdge(3, 4, 1);
    prueba("Dos componentes sin aisladas", minimaCantRutas(gDosComponentes), 0);

    return errores == 0 ? 0 : 1;
}