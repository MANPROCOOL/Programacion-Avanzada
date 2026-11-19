// Guía C3 · Ejercicio 21
// En el grafo abstracto de contactos, la marca parte en origen el día 0 y
// avanza como máximo una arista por día. Escribe los vértices alcanzados hasta
// el día cd inclusive. Retorna la cantidad. Orden libre y salida de capacidad
// G.nVertex().

#include <iostream>
#include "tGrafo.hpp"
#include "tCola.hpp"
#include <algorithm>
#include <vector>

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
int listar_infectados(tGrafo& G, tVertice origen, int cd, tVertice salida[]) {
    (void)G;
    (void)origen;
    (void)cd;
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
    tGrafo g(5,false);
    g.setEdge(0,1,1); g.setEdge(1,2,1); g.setEdge(2,3,1);
    int salida[5] = {};
    int n = listar_infectados(g,0,0,salida);
    pruebaLista("Día cero",salida,n,{0},5);
    n = listar_infectados(g,0,2,salida);
    pruebaLista("Hasta el día dos",salida,n,{0,1,2},5);
    n = listar_infectados(g,0,10,salida);
    pruebaLista("Un vértice queda fuera",salida,n,{0,1,2,3},5);
    return errores == 0 ? 0 : 1;
}
