/*
EJERCICIO 02 - DISTANCIAS ENTRE TODOS LOS PARES, USANDO DIJKSTRA
RESUELTO: Dijkstra, minVertex y distanciasTodosLosPares estan implementados.

ENUNCIADO
Calcular distanciasTodosLosPares(G, distancias) usando el Dijkstra incluido.
La matriz debe contener en distancias[origen][destino] el costo minimo del
camino entre esos vertices, sumando los pesos de los arcos.

CONTRATO
- G puede ser dirigido o no dirigido. Sus pesos son NO NEGATIVOS.
- distancias ya tiene n filas de n enteros reservadas por quien llama.
  Debes escribir todas las posiciones, sin reemplazar sus filas ni liberarlas.
- La diagonal debe valer 0, incluso para vertices aislados.
- Si no hay camino, escribe INFINITO. En consola se imprime INF.
- No agregar, eliminar ni cambiar el peso de los arcos del grafo.
- Puede haber marcas previas: tu funcion debe preparar las marcas que necesite.
- Debe poder ejecutarse otra vez sobre el mismo grafo y obtener lo mismo.
- Para n = 0 no hay posiciones que escribir ni origen para ejecutar Dijkstra.
- En estos ejercicios los costos finitos son menores que INFINITO.

DIJKSTRA YA DISPONIBLE: NO HAY QUE COMPLETARLO
La diapositiva 53 lo define como funcion externa, con la firma que aparece abajo.
Se incluye la version con minVertex por arreglo, descrita en la diapositiva 54.
distanciasTodosLosPares llama a Dijkstra una vez desde cada origen.
No necesitas pegar codigo ni agregar operaciones a los TDA.

La PPT asume D[i != s] = INFINITO antes de llamar a Dijkstra. Las marcas tambien
deben estar preparadas para cada recorrido. No cambies el TDA Grafo para esto.
Referencia: clase 08, diapositivas 28-30 y 50-54.

COMPILAR desde la carpeta que contiene tGrafo.cpp:
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/02_distancias_todos_dijkstra.cpp tGrafo.cpp -o 02_distancias_todos_dijkstra
./02_distancias_todos_dijkstra

Compila y ejecuta las pruebas: cada resultado aparece junto al esperado.
COMPLEJIDAD: O(|V|^3) tiempo con minVertex por arreglo. La matriz de salida
ocupa O(|V|^2); distanciasTodosLosPares usa O(1) espacio adicional.
El programa retorna 1 si queda algun caso incorrecto y 0 si todos pasan.
Los contenedores STL no son necesarios para resolver el ejercicio.
*/

#include "../tGrafo.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

const int INFINITO = 1000000000;
const int SIN_COMPLETAR = -2; // Las pruebas detectan posiciones no escritas con ?. 

// ===================== AUXILIAR IMPLEMENTADO =========================

tVertice minVertex(tGrafo& G, int* D) {
    const int n = G.nVertex();
    tVertice minimo = n; // Centinela: todavia no hay candidato.
    for (tVertice v = 0; v < n; ++v) {
        if (G.getMark(v) == NOVISITADO
            && (minimo == n || D[v] < D[minimo])) {
            minimo = v;
        }
    }
    return minimo;
}

// ======================= DIJKSTRA IMPLEMENTADO =======================
// Precondiciones, como en la PPT:
// - s es valido, D tiene n posiciones y los pesos son no negativos.
// - Antes de llamar, preparar D con INFINITO y las marcas con NOVISITADO.
// Esta funcion establece D[s] = 0 y modifica D y las marcas de G.

void Dijkstra(tGrafo& G, int* D, tVertice s) {
    const int n = G.nVertex();
    D[s] = 0;
    for (int i = 0; i < n; ++i) {
        tVertice v = minVertex(G, D);
        // No quedan vertices por visitar, o los restantes son inalcanzables.
        if (v == n || D[v] == INFINITO) return;

        G.setMark(v, VISITADO);
        for (tVertice w = G.first(v); w < n; w = G.next(v, w)) {
            // Usar long long en la suma evita un desbordamiento temporal.
            const long long candidato = static_cast<long long>(D[v]) + G.weight(v, w);
            if (candidato < D[w]) D[w] = static_cast<int>(candidato);
        }
    }
}

// ===================== SOLUCION DEL EJERCICIO ========================

void distanciasTodosLosPares(tGrafo& G, int** distancias) {
    const int n = G.nVertex();
    // Cada fila corresponde a un origen distinto.
    for (tVertice origen = 0; origen < n; ++origen) {
        // Dijkstra exige distancias y marcas preparadas para CADA ejecucion.
        // Se escribe directamente en la fila de ese origen: no hace falta copiar.
        for (tVertice v = 0; v < n; ++v) {
            distancias[origen][v] = INFINITO;
            G.setMark(v, NOVISITADO);
        }
        Dijkstra(G, distancias[origen], origen);
    }
}

// ====================== PRUEBAS: NO HAY QUE COMPLETAR =================

int** reservarMatriz(int n) {
    int** matriz = new int*[n];
    for (int i = 0; i < n; ++i) {
        matriz[i] = new int[n];
        for (int j = 0; j < n; ++j) matriz[i][j] = SIN_COMPLETAR;
    }
    return matriz;
}

void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; ++i) delete[] matriz[i];
    delete[] matriz;
}

void imprimirValor(int valor) {
    if (valor == INFINITO) std::cout << std::setw(7) << "INF";
    else if (valor == SIN_COMPLETAR) std::cout << std::setw(7) << "?";
    else std::cout << std::setw(7) << valor;
}

void imprimirMatriz(int** matriz, int n) {
    if (n == 0) std::cout << "  (matriz vacia)\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) imprimirValor(matriz[i][j]);
        std::cout << '\n';
    }
}

void imprimirEsperado(const int* esperado, int n) {
    if (n == 0) std::cout << "  (matriz vacia)\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) imprimirValor(esperado[i * n + j]);
        std::cout << '\n';
    }
}

bool coincide(int** resultado, const int* esperado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (resultado[i][j] != esperado[i * n + j]) return false;
    return true;
}

bool probarCaso(const char* nombre, int n, bool dirigido,
                const int aristas[][3], int cantidad, const int* esperado,
                RepresentacionGrafo representacion) {
    tGrafo G(n, dirigido, representacion);
    for (int i = 0; i < cantidad; ++i)
        G.setEdge(aristas[i][0], aristas[i][1], aristas[i][2]);
    tGrafo original(G);
    for (int v = 0; v < n; ++v) G.setMark(v, VISITADO);
    int** resultado = reservarMatriz(n);
    bool completo = false;
    bool repetible = false;
    std::cout << "\n" << nombre << '\n';
    try {
        distanciasTodosLosPares(G, resultado);
        completo = coincide(resultado, esperado, n);
        std::cout << "Mi resultado:\n";
        imprimirMatriz(resultado, n);
        // La segunda llamada detecta dependencia de las marcas de la primera.
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) resultado[i][j] = SIN_COMPLETAR;
        distanciasTodosLosPares(G, resultado);
        repetible = coincide(resultado, esperado, n);
    } catch (const std::exception& e) {
        std::cout << "Mi resultado: ERROR - " << e.what() << '\n';
    }
    std::cout << "Esperado (fila = origen, columna = destino):\n";
    imprimirEsperado(esperado, n);
    bool conservado = G.nEdges() == original.nEdges();
    for (int v = 0; v < n; ++v)
        for (int w = 0; w < n; ++w)
            if (G.isEdge(v, w) != original.isEdge(v, w)
                || G.weight(v, w) != original.weight(v, w)) conservado = false;
    const bool correcto = completo && repetible && conservado;
    std::cout << "Estado: " << (correcto ? "OK" : "ERROR") << '\n';
    liberarMatriz(resultado, n);
    return correcto;
}

int probarRepresentacion(RepresentacionGrafo representacion) {
    const int aristasA[][3] = {
        {0, 1, 10}, {0, 2, 3}, {0, 3, 20}, {2, 1, 2}, {2, 4, 15}, {1, 3, 5}
    };
    const int esperadoA[] = {
        0, 5, 3, 10, 18,
        INFINITO, 0, INFINITO, 5, INFINITO,
        INFINITO, 2, 0, 7, 15,
        INFINITO, INFINITO, INFINITO, 0, INFINITO,
        INFINITO, INFINITO, INFINITO, INFINITO, 0
    };
    const int aristasB[][3] = {{0, 1, 4}, {1, 2, 1}, {0, 2, 9}, {2, 3, 2}};
    const int esperadoB[] = {0,4,5,7, 4,0,1,3, 5,1,0,2, 7,3,2,0};
    const int aristasC[][3] = {{0, 1, 2}, {2, 3, 7}};
    const int esperadoC[] = {
        0,2,INFINITO,INFINITO,
        INFINITO,0,INFINITO,INFINITO,
        INFINITO,INFINITO,0,7,
        INFINITO,INFINITO,INFINITO,0
    };
    const int aristasD[][3] = {{0, 1, 0}, {1, 2, 5}, {2, 0, 2}, {0, 2, 9}};
    const int esperadoD[] = {0,0,5, 7,0,5, 2,2,0};
    const int esperadoE[] = {0};
    const int esperadoF[] = {0,INFINITO,INFINITO, INFINITO,0,INFINITO, INFINITO,INFINITO,0};
    int aprobados = 0;
    aprobados += probarCaso("01. Dirigido: mejorar caminos por vertices intermedios",
                            5, true, aristasA, 6, esperadoA, representacion);
    aprobados += probarCaso("02. No dirigido: costos simetricos",
                            4, false, aristasB, 4, esperadoB, representacion);
    aprobados += probarCaso("03. Dirigido desconectado: respetar sentidos y ausencia",
                            4, true, aristasC, 2, esperadoC, representacion);
    aprobados += probarCaso("04. Ciclo dirigido y arco de peso cero",
                            3, true, aristasD, 4, esperadoD, representacion);
    aprobados += probarCaso("05. Un solo vertice", 1, true, nullptr, 0, esperadoE, representacion);
    aprobados += probarCaso("06. Vertices aislados", 3, true, nullptr, 0, esperadoF, representacion);
    aprobados += probarCaso("07. Grafo vacio", 0, true, nullptr, 0, nullptr, representacion);
    return aprobados;
}

int main() {
    std::cout << "=== LISTAS DE ADYACENCIA ===\n";
    int aprobados = probarRepresentacion(RepresentacionGrafo::LISTA_ADYACENCIA);
    std::cout << "\n=== MATRIZ DE ADYACENCIA ===\n";
    aprobados += probarRepresentacion(RepresentacionGrafo::MATRIZ_ADYACENCIA);
    std::cout << "\nPruebas aprobadas: " << aprobados << "/14\n";
    return aprobados == 14 ? 0 : 1;
}
