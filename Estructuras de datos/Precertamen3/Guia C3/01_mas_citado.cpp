// Guía C3 · Ejercicio 01
// Retorna el artículo con mayor grado de entrada en O(n+m). En empate sirve
// cualquiera. Para grafo vacío usa -1.
// Prepara también la justificación que solicita la guía.

#include <iostream>
#include "tGrafo.hpp"

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
tVertice masCitado(tGrafo& G) {
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
    tGrafo g(4); g.setEdge(0,2,1); g.setEdge(1,2,1); g.setEdge(2,3,1);
    prueba("Dos citas para 2", masCitado(g), 2);
    tGrafo vacio(0); prueba("Vacío", masCitado(vacio), -1);
    return errores == 0 ? 0 : 1;
}
