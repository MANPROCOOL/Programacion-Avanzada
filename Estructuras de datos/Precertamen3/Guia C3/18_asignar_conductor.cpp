// Guía C3 · Ejercicio 18
// Retorna el vértice del conductor que puede llegar al pasajero con menor
// costo. En empate sirve cualquiera. Retorna -1 si ninguno llega o no hay
// conductores. Dijkstra está disponible para arcos con pesos no negativos. En
// un digrafo se mide conductor -> pasajero.

#include <iostream>
#include "tGrafo.hpp"
#include <limits>

namespace {
bool pendiente = false;
}

const int INFINITO = std::numeric_limits<int>::max();

// D debe tener G.nVertex() posiciones. Dijkstra prepara D y las marcas.
void Dijkstra(tGrafo& G, int D[], tVertice origen) {
    const int n = G.nVertex();
    for (tVertice v = 0; v < n; ++v) {
        D[v] = INFINITO;
        G.setMark(v, NOVISITADO);
    }
    D[origen] = 0;
    for (int paso = 0; paso < n; ++paso) {
        tVertice v = n;
        for (tVertice u = 0; u < n; ++u)
            if (G.getMark(u) == NOVISITADO && (v == n || D[u] < D[v])) v = u;
        if (v == n || D[v] == INFINITO) return;
        G.setMark(v, VISITADO);
        for (tVertice w = G.first(v); w < n; w = G.next(v,w)) {
            const long long costo = static_cast<long long>(D[v]) + G.weight(v,w);
            if (costo < D[w]) D[w] = static_cast<int>(costo);
        }
    }
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
tVertice asignar_conductor(tVertice pasajero, tGrafo& G, tVertice* conductores, int nc) {
    (void)pasajero;
    (void)G;
    (void)conductores;
    (void)nc;
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
    tGrafo g(5);
    g.setEdge(0,2,2); g.setEdge(2,4,1); g.setEdge(1,4,6); g.setEdge(4,3,1);
    tVertice candidatos[] = {1,3,0};
    prueba("Tramos dirigidos y ruta indirecta",asignar_conductor(4,g,candidatos,3),0);
    prueba("Nadie puede llegar",asignar_conductor(0,g,candidatos,2),-1);
    prueba("Sin conductores",asignar_conductor(4,g,nullptr,0),-1);
    return errores == 0 ? 0 : 1;
}
