/*
EJERCICIO 04 - DETECTAR CICLOS EN UN GRAFO DIRIGIDO CON KAHN

Implementa tieneCicloKahn(G) usando tGrafo y tCola.
G se construye con dirigido = true. Los pesos son irrelevantes.

1. Cuenta los arcos que entran a cada vértice (su grado de entrada).
2. Encola todos los vértices cuyo grado de entrada sea cero.
3. Al sacar v, descuenta sus arcos salientes. Si el grado de un vecino
   llega a cero, encola ese vecino: ya se procesaron sus predecesores.
4. Si la cola se vacía y quedan vértices pendientes, existe un ciclo.

Por qué funciona:
- Cada vértice de un ciclo conserva un arco entrante desde el propio ciclo
  hasta que salga el primero de ellos. Por eso ninguno puede salir primero.
- Si quedan vértices cuando se agota la cola, cada pendiente tiene al menos
  un predecesor pendiente. Al seguir esos predecesores, algún vértice se
  repite y los arcos entre esas dos apariciones forman un ciclo.

Ejemplo sin ciclo: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3.
Grados iniciales: [0, 1, 1, 2]. La cola parte con [0].
Al sacar 0 entran 1 y 2. Al sacar 1, el grado de 3 baja a 1.
Al sacar 2 baja a 0 y entra 3. Salen los cuatro: no hay ciclo.
Si agregas 3 -> 1, solo salen 0 y 2. Quedan pendientes 1 y 3.

Tiempo: O(V + E) con listas de adyacencia, O(V^2) con matriz.
Espacio auxiliar: O(V). La cola comienza con todas las fuentes, por lo
que también se detectan ciclos en componentes desconectadas.

Compilar desde Precertamen3:
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/04_ciclos_dirigidos_kahn.cpp tGrafo.cpp tCola.cpp -o ciclos_kahn
./ciclos_kahn
*/

#include "../tGrafo.hpp"
#include "../tCola.hpp"
#include <iostream>

bool tieneCicloKahn(tGrafo& G) {
    const int n = G.nVertex();
    tCola pendientes;
    int* gradoEntrada = new int[n]();
    int procesados = 0;

    // Cada arco v -> w suma uno al grado de entrada de w.
    for (tVertice v = 0; v < n; ++v) {
        for (tVertice w = G.first(v); w < n; w = G.next(v, w)) {
            ++gradoEntrada[w];
        }
    }

    for (tVertice v = 0; v < n; ++v) {
        if (gradoEntrada[v] == 0) {
            pendientes.enqueue(v);
        }
    }

    while (!pendientes.isEmpty()) {
        const tVertice v = pendientes.frontValue();
        pendientes.dequeue();
        ++procesados;

        // Simula quitar los arcos v -> w actualizando solo los grados.
        for (tVertice w = G.first(v); w < n; w = G.next(v, w)) {
            --gradoEntrada[w];
            if (gradoEntrada[w] == 0) {
                pendientes.enqueue(w);
            }
        }
    }

    delete[] gradoEntrada;
    return procesados < n;
}

int main() {
    tGrafo G(4, true);
    G.setEdge(0, 1, 1);
    G.setEdge(0, 2, 1);
    G.setEdge(1, 3, 1);
    G.setEdge(2, 3, 1);

    const bool cicloEnDiamante = tieneCicloKahn(G);
    std::cout << std::boolalpha;
    std::cout << "Diamante (esperado: false): " << cicloEnDiamante << '\n';

    G.setEdge(3, 1, 1);
    const bool cicloConArcoDeVuelta = tieneCicloKahn(G);
    std::cout << "Con arco 3 -> 1 (esperado: true): "
              << cicloConArcoDeVuelta << '\n';

    return !cicloEnDiamante && cicloConArcoDeVuelta ? 0 : 1;
}
