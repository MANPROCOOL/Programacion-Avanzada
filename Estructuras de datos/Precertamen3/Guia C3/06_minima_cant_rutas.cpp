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
    tGrafo g(5,false); g.setEdge(0,1,1);
    prueba("Tres aisladas",minimaCantRutas(g),2);
    g.setEdge(2,3,1);
    prueba("Una aislada",minimaCantRutas(g),1);
    g.setEdge(3,4,1);
    prueba("Dos componentes sin aisladas",minimaCantRutas(g),0);
    return errores == 0 ? 0 : 1;
}
