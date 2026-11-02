/*
EJERCICIO 03 - CAMINO CON MENOR CANTIDAD DE ARCOS
RESUELTO: Dijkstra sobre un grafo auxiliar con todos los pesos iguales a 1.

ENUNCIADO
Resolver caminoMenosArcos(G, origen, destino, camino), usando Dijkstra.
Segun la indicacion del profesor, reemplazar cada peso por 1 antes de ejecutarlo.
Debe reconstruir un camino entre esos vertices con la menor cantidad de arcos.
Aqui se minimiza el NUMERO DE ARCOS; los pesos almacenados en G se ignoran.

CONTRATO
- G puede ser dirigido o no dirigido; respetar el sentido de sus arcos.
- origen y destino son vertices validos; el grafo de esta funcion tiene n >= 1.
- camino ya es un arreglo reservado con capacidad n por quien llama.
- Si existe un camino minimo de k arcos, retornar k y escribir sus k+1 vertices
  en camino[0..k], en orden desde origen hasta destino.
- Si origen == destino, retornar 0 y escribir camino[0] = origen.
- Si no existe camino, retornar -1. En ese caso no se examina el arreglo camino.
- Si hay varios caminos minimos, cualquiera es valido. No debes enumerarlos todos.
- No cambiar arcos ni pesos del grafo. Puedes utilizar sus marcas, pero preparar
  las que necesites: puede haber marcas de recorridos anteriores.
- La funcion debe poder llamarse repetidamente sobre el mismo grafo.

EXPLICACION
Si todos los arcos pesan 1, un camino de k arcos tiene costo 1+...+1 = k.
Por eso, el camino de menor costo que encuentra Dijkstra tambien tiene el
menor numero de arcos, independientemente de los pesos originales.

1. Crear un grafo auxiliar con los mismos vertices y conexiones, con peso 1.
2. Ejecutar Dijkstra desde origen, guardando anterior[w] cada vez que mejora D[w].
3. Si destino es inalcanzable, retornar -1.
4. Si es alcanzable, seguir anterior[] desde destino hacia origen. Escribir los
   vertices de atras hacia adelante en camino[], para entregarlo en el orden pedido.

El auxiliar es dirigido: en un original no dirigido se copian ambos sentidos
que ya entrega first/next. Asi se conserva exactamente la conectividad original.
Se usa matriz en el auxiliar para asignar los pesos en O(1) por arco.
El grafo original conserva sus pesos y conexiones; no necesita cambios en el TDA.

COMPLEJIDAD
O(|V|^2) tiempo y O(|V|^2) espacio auxiliar, incluyendo la matriz del grafo
auxiliar. Los arreglos de distancias y predecesores usan O(|V|). Dijkstra usa
minVertex por arreglo, como en la alternativa de la diapositiva 54.

Referencia: clase 08, diapositivas 50-54. Se agrega el arreglo anterior[] para
recuperar el camino, ademas del costo que calcula la version de la PPT.

COMPILAR desde la carpeta que contiene los TDA:
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/03_camino_menos_arcos_dijkstra.cpp tGrafo.cpp -o 03_camino_menos_arcos_dijkstra
./03_camino_menos_arcos_dijkstra

Cada prueba imprime el resultado y luego el esperado. Se comprueba tambien
que los pesos originales no hayan cambiado.
El programa retorna 1 si queda algun caso incorrecto y 0 si todos pasan.
No necesitas contenedores STL para resolver el ejercicio.
*/

#include "../tGrafo.hpp"
#include <iostream>
#include <stdexcept>

const int INFINITO = 1000000000;

// ====================== AUXILIARES DE DIJKSTRA ========================

tVertice minVertex(tGrafo& G, int* D) {
    const int n = G.nVertex();
    tVertice minimo = n;
    for (tVertice v = 0; v < n; ++v) {
        if (G.getMark(v) == NOVISITADO
            && (minimo == n || D[v] < D[minimo])) minimo = v;
    }
    return minimo;
}

// Version de Dijkstra que tambien registra el predecesor de cada vertice.
// D, anterior y las marcas deben estar preparados antes de llamar.
void Dijkstra(tGrafo& G, int* D, tVertice origen, tVertice* anterior) {
    const int n = G.nVertex();
    D[origen] = 0;
    for (int i = 0; i < n; ++i) {
        tVertice v = minVertex(G, D);
        if (v == n || D[v] == INFINITO) return;
        G.setMark(v, VISITADO);

        for (tVertice w = G.first(v); w < n; w = G.next(v, w)) {
            const long long candidato = static_cast<long long>(D[v]) + G.weight(v, w);
            if (candidato < D[w]) {
                D[w] = static_cast<int>(candidato);
                anterior[w] = v; // El mejor camino a w llega ahora desde v.
            }
        }
    }
}

// ===================== SOLUCION DEL EJERCICIO =========================

int caminoMenosArcos(tGrafo& G, tVertice origen, tVertice destino, tVertice camino[]) {
    const int n = G.nVertex();
    tGrafo unitario(n, true, RepresentacionGrafo::MATRIZ_ADYACENCIA);

    // Copiar las conexiones y cambiar TODOS sus pesos a 1.
    // Se enumeran los vecinos de G y se modifica otro grafo.
    for (tVertice v = 0; v < n; ++v)
        for (tVertice w = G.first(v); w < n; w = G.next(v, w))
            unitario.setEdge(v, w, 1);

    int* D = new int[n];
    tVertice* anterior = new tVertice[n];
    for (tVertice v = 0; v < n; ++v) {
        D[v] = INFINITO;
        anterior[v] = -1;
        unitario.setMark(v, NOVISITADO);
    }

    Dijkstra(unitario, D, origen, anterior);
    const int arcos = D[destino];
    if (arcos == INFINITO) {
        delete[] D;
        delete[] anterior;
        return -1;
    }

    // Como cada arco pesa 1, D[destino] es exactamente la cantidad de arcos.
    // Los predecesores vienen al reves; escribir desde el final evita otra inversion.
    tVertice actual = destino;
    for (int i = arcos; i >= 0; --i) {
        camino[i] = actual;
        if (i > 0) actual = anterior[actual];
    }

    delete[] D;
    delete[] anterior;
    return arcos;
}

// ====================== PRUEBAS: NO HAY QUE COMPLETAR =================

void imprimirCamino(const tVertice camino[], int arcos) {
    for (int i = 0; i <= arcos; ++i) {
        if (i != 0) std::cout << " -> ";
        std::cout << camino[i];
    }
}

bool caminoValido(tGrafo& G, const tVertice camino[], int arcos,
                  tVertice origen, tVertice destino) {
    const int n = G.nVertex();
    if (arcos < 0 || arcos >= n) return false;
    for (int i = 0; i <= arcos; ++i)
        if (camino[i] < 0 || camino[i] >= n) return false;
    if (camino[0] != origen || camino[arcos] != destino) return false;
    for (int i = 0; i < arcos; ++i)
        if (!G.isEdge(camino[i], camino[i + 1])) return false;
    return true;
}

bool probarCaso(const char* nombre, int n, bool dirigido,
                const int aristas[][3], int cantidad, int origen, int destino,
                int arcosEsperados, const tVertice ejemploEsperado[],
                RepresentacionGrafo representacion) {
    tGrafo G(n, dirigido, representacion);
    for (int i = 0; i < cantidad; ++i)
        G.setEdge(aristas[i][0], aristas[i][1], aristas[i][2]);
    tGrafo original(G);
    for (int v = 0; v < n; ++v) G.setMark(v, VISITADO);
    tVertice* camino = new tVertice[n];
    for (int i = 0; i < n; ++i) camino[i] = -9;

    bool correcto = false;
    std::cout << "\n" << nombre << " (" << origen << " a " << destino << ")\n";
    try {
        const int arcos = caminoMenosArcos(G, origen, destino, camino);
        std::cout << "Mi resultado: " << arcos << " arco(s); ";
        if (arcos == -1) std::cout << "sin camino";
        else if (arcos >= 0 && arcos < n) imprimirCamino(camino, arcos);
        else std::cout << "retorno fuera del contrato";
        std::cout << '\n';

        correcto = arcos == arcosEsperados;
        if (arcos >= 0) correcto = correcto && caminoValido(original, camino, arcos, origen, destino);

        // Segunda llamada: las marcas de la primera no deben impedir el recorrido.
        for (int i = 0; i < n; ++i) camino[i] = -9;
        const int repetido = caminoMenosArcos(G, origen, destino, camino);
        correcto = correcto && repetido == arcosEsperados;
        if (repetido >= 0)
            correcto = correcto && caminoValido(original, camino, repetido, origen, destino);
    } catch (const std::exception& e) {
        std::cout << "Mi resultado: ERROR - " << e.what() << '\n';
        correcto = false;
    }
    std::cout << "Esperado: " << arcosEsperados << " arco(s); ";
    if (arcosEsperados == -1) std::cout << "sin camino";
    else {
        std::cout << "ejemplo: ";
        imprimirCamino(ejemploEsperado, arcosEsperados);
        std::cout << " (se acepta cualquier camino minimo valido)";
    }
    std::cout << '\n';

    correcto = correcto && G.nEdges() == original.nEdges();
    for (int v = 0; v < n; ++v)
        for (int w = 0; w < n; ++w)
            if (G.isEdge(v, w) != original.isEdge(v, w)
                || G.weight(v, w) != original.weight(v, w)) correcto = false;

    std::cout << "Estado: " << (correcto ? "OK" : "ERROR") << '\n';
    delete[] camino;
    return correcto;
}

int probarRepresentacion(RepresentacionGrafo representacion) {
    const int a[][3] = {{0,1,1}, {1,2,1}, {2,3,1}};
    const tVertice caminoA[] = {0,1,2,3};
    const int b[][3] = {{0,3,50}, {0,1,1}, {1,2,1}, {2,3,1}};
    const tVertice caminoB[] = {0,3};
    const int c[][3] = {{0,1,1}, {0,2,1}, {1,3,1}, {2,3,1}};
    const tVertice caminoC[] = {0,1,3};
    const tVertice caminoD[] = {3,2,1,0};
    const int e[][3] = {{0,1,1}, {1,2,1}, {2,0,1}, {2,3,1}};
    const tVertice caminoE[] = {1,2,3};
    const tVertice caminoF[] = {2};
    const int g[][3] = {{0,1,1}, {2,3,1}, {3,4,1}};
    const tVertice caminoG[] = {2,3,4};
    const int h[][3] = {{0,0,1}, {0,1,1}};
    const tVertice caminoH[] = {0,1};

    int aprobados = 0;
    aprobados += probarCaso("01. Cadena dirigida", 4, true, a, 3, 0, 3, 3, caminoA, representacion);
    aprobados += probarCaso("02. Menos arcos aunque el costo sea mayor", 4, true, b, 4,
                            0, 3, 1, caminoB, representacion);
    aprobados += probarCaso("03. Empate: aceptar cualquiera de dos caminos", 4, true, c, 4,
                            0, 3, 2, caminoC, representacion);
    aprobados += probarCaso("04. Respetar el sentido: no hay camino de regreso", 4, true, a, 3,
                            3, 0, -1, nullptr, representacion);
    aprobados += probarCaso("05. Cadena no dirigida: si hay regreso", 4, false, a, 3,
                            3, 0, 3, caminoD, representacion);
    aprobados += probarCaso("06. Ciclo dirigido", 4, true, e, 4, 1, 3, 2, caminoE, representacion);
    aprobados += probarCaso("07. Origen igual al destino", 4, true, a, 3,
                            2, 2, 0, caminoF, representacion);
    aprobados += probarCaso("08. Destino en otra componente", 5, false, g, 3,
                            0, 4, -1, nullptr, representacion);
    aprobados += probarCaso("09. Camino en componente que no contiene al 0", 5, false, g, 3,
                            2, 4, 2, caminoG, representacion);
    aprobados += probarCaso("10. Un lazo no mejora el camino", 2, true, h, 2,
                            0, 1, 1, caminoH, representacion);
    return aprobados;
}

int main() {
    std::cout << "=== LISTAS DE ADYACENCIA ===\n";
    int aprobados = probarRepresentacion(RepresentacionGrafo::LISTA_ADYACENCIA);
    std::cout << "\n=== MATRIZ DE ADYACENCIA ===\n";
    aprobados += probarRepresentacion(RepresentacionGrafo::MATRIZ_ADYACENCIA);
    std::cout << "\nPruebas aprobadas: " << aprobados << "/20\n";
    return aprobados == 20 ? 0 : 1;
}
