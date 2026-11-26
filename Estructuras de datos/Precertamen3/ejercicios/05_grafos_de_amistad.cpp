/*
EJERCICIO 05 - GRAFOS DE AMISTAD (PIZARRA C3)

Cada vertice representa a una persona. Una arista no dirigida indica que
dos personas son amigas directas. Los pesos son irrelevantes.

a) contarAmigosIndirectos(G, v)
   Cuenta las personas distintas de v que no son sus amigas directas y
   que comparten al menos un amigo con v. Cuenta a cada persona una sola
   vez, aunque comparta varios amigos con v.

b) distanciaSocial(G, v, u)
   Para dos personas distintas, calcula el minimo numero de intermediarios
   entre v y u. Retorna 0 si son amigas directas y -1 si no hay camino.

Usa tGrafo y tCola. Las funciones deben poder llamarse varias veces sobre
el mismo grafo sin cambiar sus aristas.

Compilar desde Precertamen3:
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/05_grafos_de_amistad.cpp tGrafo.cpp tCola.cpp -o amistad
./amistad
*/

#include "../tGrafo.hpp"
#include "../tCola.hpp"
#include <iostream>

int contarAmigosIndirectos(tGrafo& G, tVertice v) {
    // TODO: implementar el inciso a).
    (void)G;
    (void)v;
    return -2;
}

int distanciaSocial(tGrafo& G, tVertice v, tVertice u) {
    // TODO: implementar el inciso b).
    (void)G;
    (void)v;
    (void)u;
    return -2;
}

bool probarCaso(const char* nombre, int obtenido, int esperado) {
    std::cout << nombre << '\n' << "  Mi resultado: ";
    if (obtenido == -2) {
        std::cout << "pendiente";
    } else {
        std::cout << obtenido;
    }
    const bool correcto = obtenido == esperado;
    const char* estado = obtenido == -2 ? "PENDIENTE" : (correcto ? "OK" : "ERROR");
    std::cout << " | Esperado: " << esperado << " [" << estado << "]\n";
    return correcto;
}

int main() {
    enum { A, B, C, D, E, F, G, H, X, Y };
    tGrafo pizarra(10, false);
    pizarra.setEdge(A, C, 1);
    pizarra.setEdge(C, B, 1);
    pizarra.setEdge(B, D, 1);
    pizarra.setEdge(D, F, 1);
    pizarra.setEdge(F, E, 1);
    pizarra.setEdge(E, A, 1);
    pizarra.setEdge(F, X, 1);
    pizarra.setEdge(F, Y, 1);
    pizarra.setEdge(Y, G, 1);
    pizarra.setEdge(Y, H, 1);

    int errores = 0;
    if (!probarCaso("Pizarra: amigos indirectos de A",
                    contarAmigosIndirectos(pizarra, A), 2)) errores++;
    if (!probarCaso("Pizarra: distancia social A-C",
                    distanciaSocial(pizarra, A, C), 0)) errores++;
    if (!probarCaso("Pizarra: distancia social A-F",
                    distanciaSocial(pizarra, A, F), 1)) errores++;
    if (!probarCaso("Pizarra: distancia social A-H",
                    distanciaSocial(pizarra, A, H), 3)) errores++;

    // Desde 0 se llega a 3 tanto por 1 como por 2. El vertice 4 esta aislado.
    tGrafo rombo(5, false);
    rombo.setEdge(0, 1, 1);
    rombo.setEdge(0, 2, 1);
    rombo.setEdge(1, 3, 1);
    rombo.setEdge(2, 3, 1);

    if (!probarCaso("Rombo: contar una sola vez a la persona 3",
                    contarAmigosIndirectos(rombo, 0), 1)) errores++;
    if (!probarCaso("Rombo: distancia social 0-4",
                    distanciaSocial(rombo, 0, 4), -1)) errores++;
    if (!probarCaso("Rombo: amigos indirectos de la persona aislada",
                    contarAmigosIndirectos(rombo, 4), 0)) errores++;

    rombo.setEdge(0, 3, 1);
    if (!probarCaso("Rombo con diagonal: excluir a un amigo directo",
                    contarAmigosIndirectos(rombo, 0), 0)) errores++;

    return errores == 0 ? 0 : 1;
}
