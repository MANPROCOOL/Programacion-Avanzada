#include <cstdlib>
#include <iostream>
#include <string>
#include "nodo.h"
#include "abb.h"
#include "pila_abb.h"

// Cada caso corre por separado para que un fallo no detenga los siguientes.
// La solucion y los TDA se mantienen en sus archivos originales.
void ejecutarCaso(int caso) {
    tABB A;
    tipoElem resultado = -1;
    const std::string acciones[] = {"comer", "correr", "huir", "atacar"};

    if (caso != 1) {
        // Mismos datos y mismo orden de insercion que en los ejemplos del PDF.
        A.insert(15, "-");
        A.insert(9, "-");
        A.insert(7, "huir");
        A.insert(12, "-");
        A.insert(14, "correr");
        A.insert(20, "-");
        A.insert(16, "correr");
        A.insert(21, "huir");
    }

    A.decisionesMinimas(acciones[caso - 1], &resultado);
    std::cout << resultado << std::endl;
    A.clear();
}

int main(int argc, char* argv[]) {
    // Modo interno: ejecutar un solo caso en este proceso.
    if (argc == 3 && std::string(argv[1]) == "--caso") {
        const int caso = std::atoi(argv[2]);
        if (caso < 1 || caso > 4) return 1;
        ejecutarCaso(caso);
        return 0;
    }

    const std::string descripciones[] = {
        "Arbol vacio, buscar comer",
        "Arbol de 8 nodos, buscar correr",
        "Arbol de 8 nodos, buscar huir",
        "Arbol de 8 nodos, buscar atacar"
    };
    const tipoElem esperados[] = {-1, 16, 7, -1};

    // Proteger la ruta del ejecutable, incluso si contiene espacios.
#ifdef _WIN32
    const std::string programa = "\"" + std::string(argv[0]) + "\"";
#else
    std::string programa = "'";
    for (char c : std::string(argv[0])) {
        if (c == '\'') programa += "'\\''";
        else programa += c;
    }
    programa += "'";
#endif

    for (int i = 0; i < 4; ++i) {
        std::cout << "Caso " << i + 1 << ": " << descripciones[i] << '\n';
        std::cout << "Tu output: " << std::flush;

        const std::string llamada = programa + " --caso " + std::to_string(i + 1);
#ifdef _WIN32
        const std::string comando = "\"" + llamada + "\" 2>NUL";
#else
        const std::string comando = "(ulimit -c 0; " + llamada + "; exit $?) 2>/dev/null";
#endif
        const int estado = std::system(comando.c_str());
        if (estado != 0) {
            std::cout << "ERROR DE EJECUCION (no se obtuvo un resultado)\n";
        }

        std::cout << "Esperado: " << esperados[i] << "\n\n";
    }

    return 0;
}
