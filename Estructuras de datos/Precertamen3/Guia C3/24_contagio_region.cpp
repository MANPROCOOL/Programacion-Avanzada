// Guía C3 · Ejercicio 24
// Modelo abstracto de la guía. Cada vértice tiene un valor fijo grado[i] y
// cada arista adyacente tiene peso positivo d(i,j). Desde i se admite la
// transición a j si grado[i] / d(i,j) > 1. Retorna si todos los vértices se
// alcanzan desde inicio. El valor de la comuna no cambia al alcanzarla.

#include <iostream>
#include "tGrafo.hpp"
#include "tCola.hpp"

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
bool contagioRegion(tGrafo& G, tVertice inicio, const int grado[]) {

    // Tengo que usar un bfs e ir comparando las distancias entre comunas adyacentes y grados
    // ademas tendre un arreglo booleano con todos los vertices para saber si estan contagiados

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
    std::cout << std::boolalpha;
    tGrafo g(3,false); g.setEdge(0,1,2); g.setEdge(1,2,3);
    int supera[] = {3,4,1};
    prueba("Los dos pasos cumplen",contagioRegion(g,0,supera),true);
    int igual[] = {3,3,1};
    prueba("La igualdad bloquea el segundo paso",contagioRegion(g,0,igual),false);
    tGrafo aislada(1,false); int valor[] = {1};
    prueba("Solo la comuna inicial",contagioRegion(aislada,0,valor),true);
    return errores == 0 ? 0 : 1;
}
