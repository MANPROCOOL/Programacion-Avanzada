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
    const int n = G.nVertex();

    // Si no hay artículos, devolvemos -1 según el esqueleto del ejercicio.
    if (n == 0) return -1;

    // Cada posición guarda las citas que recibe un artículo.
    int* citas = new int[n](); // Los paréntesis en new int[n]() dejan todos los contadores en cero.

    // Cada v es un artículo cuya bibliografía vamos a revisar.
    for (tVertice v = 0; v < n; ++v) {
        // first(v) entrega el primer artículo que cita v.
        // next(v, w) entrega el siguiente después de w.
        // Ambos devuelven n cuando ya no hay más vecinos.
        for (tVertice w = G.first(v); w < n; w = G.next(v, w)) {
            // El arco v → w significa que v cita a w.
            // Por ejemplo, al ver 0 → 2, el artículo 2 recibe una cita.
            ++citas[w];
        }
    }

    // Ya contamos todas las citas. Partimos con el artículo 0
    // como candidato y lo comparamos con cada artículo restante.
    tVertice mejor = 0;
    for (tVertice v = 1; v < n; ++v) {
        // Actualizamos solo si v tiene más citas. En caso de empate
        // queda el primer artículo encontrado, el de menor índice.
        if (citas[v] > citas[mejor]) {
            mejor = v;
        }
    }

    delete[] citas;

    // mejor guarda el identificador del artículo más citado.
    return mejor;
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
