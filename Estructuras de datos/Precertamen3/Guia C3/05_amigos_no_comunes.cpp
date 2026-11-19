// Guía C3 · Ejercicio 05
// Escribe en salida los vecinos de v2 que no son vecinos de v1. Retorna la
// cantidad. El orden es libre y la capacidad es G.nVertex(). Usa
// O(grado(v1)+grado(v2)). Se aplica la diferencia de conjuntos literal.
// Prepara también la justificación que solicita la guía.

#include <iostream>
#include "tGrafo.hpp"
#include <algorithm>
#include <vector>

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
int amigosNoComunes(tGrafo& G, tVertice v1, tVertice v2, tVertice salida[]) {
    (void)G;
    (void)v1;
    (void)v2;
    (void)salida;
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
void imprimir(const std::vector<int>& valores) {
    std::cout << '[';
    for (std::size_t i = 0; i < valores.size(); ++i) {
        if (i != 0) std::cout << ", ";
        std::cout << valores[i];
    }
    std::cout << ']';
}
void pruebaLista(const char* nombre, const int salida[], int n,
                 std::vector<int> esperado, int capacidad) {
    std::cout << nombre << '\n' << "  Mi resultado: ";
    std::vector<int> obtenido;
    bool rango = n >= 0 && n <= capacidad;
    if (pendiente) std::cout << "pendiente";
    else if (rango) {
        obtenido.assign(salida, salida + n);
        imprimir(obtenido);
    } else std::cout << "cantidad inválida: " << n;
    std::cout << " | Esperado (orden libre): ";
    imprimir(esperado);
    std::sort(obtenido.begin(), obtenido.end());
    std::sort(esperado.begin(), esperado.end());
    estado(rango && obtenido == esperado);
}
}

int main() {
    tGrafo g(6,false);
    g.setEdge(0,2,1); g.setEdge(0,4,1);
    g.setEdge(1,2,1); g.setEdge(1,3,1); g.setEdge(1,5,1);
    int salida[6] = {};
    int n = amigosNoComunes(g,0,1,salida);
    pruebaLista("Amigos exclusivos de 1", salida,n,{3,5},6);
    n = amigosNoComunes(g,0,0,salida);
    pruebaLista("Misma persona",salida,n,{},6);
    return errores == 0 ? 0 : 1;
}
