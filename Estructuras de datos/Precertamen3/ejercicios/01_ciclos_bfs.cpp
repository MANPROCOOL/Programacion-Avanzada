/*
EJERCICIO 01 - DETECTAR CICLOS CON BFS (RESUELTO)

ENUNCIADO
Implementar bool tieneCicloBFS(tGrafo& G), que indique si un grafo NO DIRIGIDO
contiene al menos un ciclo. Debe funcionar aunque el grafo sea desconectado.
Usar el TDA Grafo y el TDA Cola de la clase 08, sin contenedores STL.

PRECONDICIONES Y RESULTADO
- Construir G con tGrafo G(n, false); false significa no dirigido.
- La funcion devuelve true si existe un ciclo y false si no existe.
  Detecta la existencia: no enumera ni devuelve los vertices de cada ciclo.
- Los pesos no afectan esta pregunta; en las pruebas todas las aristas pesan 1.
- La funcion reinicia las marcas al comenzar y las modifica durante el BFS.
- El TDA admite lazos: una arista de un vertice hacia si mismo cuenta como ciclo.
  No admite aristas paralelas: setEdge repetido actualiza el peso.

IDEA DE LA SOLUCION
En un grafo no dirigido, agregar 0--1 hace que 1 sea vecino de 0 y viceversa.
Si llegamos de 0 a 1, al revisar los vecinos de 1 volveremos a encontrar a 0.
Ese regreso por la misma arista NO basta para afirmar que hay un ciclo.

Por eso guardamos padre[w]: el vertice desde el cual descubrimos a w.
Al revisar una arista v--w hay dos situaciones:
1. w no esta visitado: marcamos w, guardamos padre[w] = v y lo encolamos.
2. w ya esta visitado: si w != padre[v], encontramos una conexion adicional
   a los enlaces del arbol BFS. Esa conexion cierra un ciclo.

Marcar AL ENCOLAR evita que un vertice se descubra y encole varias veces.
Un for exterior inicia un BFS en cada componente todavia no visitada.
Asi tambien encontramos ciclos que no son alcanzables desde el vertice 0.

EJEMPLO: TRIANGULO CON ARISTAS 0--1, 0--2 Y 1--2
- Sacamos 0 de la cola. Descubrimos 1 y 2; ambos quedan con padre 0.
- Sacamos 1. Su vecino 0 es su padre: ignoramos ese regreso.
- Su vecino 2 ya esta visitado y no es padre de 1: existe un ciclo.
  El ciclo de este ejemplo es 0 -> 1 -> 2 -> 0.

POR QUE FUNCIONA
Las aristas que descubren vertices nuevos forman un bosque de arboles BFS.
Si aparece una arista hacia un vecino ya descubierto que no es el padre,
hay otro camino entre esos extremos dentro del arbol: juntos forman un ciclo.
Si el grafo tiene un ciclo, al recorrerlo aparece alguna arista adicional a
las del bosque BFS. Por lo tanto, el criterio necesariamente lo detecta.

COMPLEJIDAD
Con listas de adyacencia: O(|V| + |E|) tiempo y O(|V|) espacio auxiliar.
Con matriz de adyacencia: O(|V|^2) tiempo y O(|V|) espacio auxiliar.
En no dirigidos se examina cada arista en ambos sentidos; sigue siendo O(|E|).

COMPILAR DESDE LA CARPETA QUE CONTIENE LOS TDA
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/01_ciclos_bfs.cpp tGrafo.cpp tCola.cpp -o 01_ciclos_bfs
./01_ciclos_bfs

Este criterio de padre corresponde a grafos NO dirigidos. En un digrafo, una
arista hacia un vertice visitado no necesariamente cierra un ciclo dirigido.
*/

#include "../tGrafo.hpp"
#include "../tCola.hpp"
#include <iostream>

// ======================= SOLUCION DEL EJERCICIO =======================

bool tieneCicloBFS(tGrafo& G) {
    const int n = G.nVertex();

    // padre[v] indica desde qué vértice descubrimos a v.
    // Lo necesitamos porque, en un grafo no dirigido, cada arista
    // aparece en ambos sentidos: volver al padre no forma un ciclo.
    int* padre = new int[n];

    // Reiniciamos las marcas para no depender de recorridos anteriores.
    // -1 significa que el vértice todavía no tiene padre.
    for (tVertice v = 0; v < n; ++v) {
        G.setMark(v, NOVISITADO);
        padre[v] = -1;
    }

    // La cola guarda los vértices descubiertos cuyos vecinos
    // todavía debemos revisar.
    tCola pendientes;
    bool hayCiclo = false;

    // Un BFS solo alcanza la componente de su vértice inicial.
    // Por eso iniciamos otro desde cada vértice que siga sin visitar.
    for (tVertice inicio = 0; inicio < n && !hayCiclo; ++inicio) {

        // Si ya fue visitado, pertenece a una componente ya recorrida.
        if (G.getMark(inicio) == VISITADO) continue;

        // La raíz de esta componente conserva padre[inicio] = -1.
        G.setMark(inicio, VISITADO);
        pendientes.enqueue(inicio);

        // Continuamos mientras queden vértices pendientes
        // y todavía no hayamos encontrado un ciclo.
        while (pendientes.size() != 0 && !hayCiclo) {

            // Consultamos el frente antes de eliminarlo,
            // porque dequeue() no retorna el elemento.
            tVertice v = pendientes.frontValue();
            pendientes.dequeue();

            // Recorremos todos los vecinos w del vértice v.
            // first() y next() retornan n cuando no quedan vecinos.
            for (tVertice w = G.first(v);
                 w < n && !hayCiclo;
                 w = G.next(v, w)) {

                if (G.getMark(w) == NOVISITADO) {

                    // Descubrimos un vértice nuevo a través de v.
                    // Lo marcamos AHORA para evitar que otro vértice
                    // lo vuelva a encolar antes de que sea procesado.
                    G.setMark(w, VISITADO);
                    padre[w] = v;
                    pendientes.enqueue(w);

                } else if (w != padre[v]) {

                    // w ya estaba visitado y no es el padre de v.
                    // Los enlaces de padre ya conectan a v con w;
                    // esta arista adicional cierra un ciclo.
                    //
                    // Si w fuera el padre de v, solo estaríamos
                    // recorriendo al revés la arista que descubrimos.
                    hayCiclo = true;
                }
            }
        }
    }

    // Liberamos el arreglo tanto si encontramos un ciclo
    // como si terminamos de recorrer el grafo sin encontrarlo.
    delete[] padre;

    // Si quedaron elementos en pendientes, el destructor de tCola
    // los libera automáticamente al terminar la función.
    return hayCiclo;
}


// ======================== PRUEBAS AUTOMATICAS =========================
// Puedes concentrarte primero en la funcion anterior. Esta parte construye
// grafos conocidos y compara lo obtenido con lo esperado, sin pedir inputs.

bool probarCaso(const char* nombre, int n, const int aristas[][2], int cantidad,
                bool esperado, RepresentacionGrafo representacion) {
    tGrafo G(n, false, representacion);
    for (int i = 0; i < cantidad; ++i)
        G.setEdge(aristas[i][0], aristas[i][1], 1);

    // Comprobar que la funcion inicializa sus propias marcas.
    for (int v = 0; v < n; ++v) G.setMark(v, 77);

    const int aristasAntes = G.nEdges();
    const bool resultado = tieneCicloBFS(G);
    const bool repetido = tieneCicloBFS(G);
    const bool correcto = resultado == esperado && repetido == esperado
                          && G.nEdges() == aristasAntes;

    std::cout << nombre << '\n'
              << "  Mi resultado: " << resultado
              << " | Esperado: " << esperado
              << " | " << (correcto ? "OK" : "ERROR") << '\n';
    return correcto;
}

int probarRepresentacion(RepresentacionGrafo representacion) {
    const int unaArista[][2] = {{0, 1}};
    const int arbol[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}};
    const int triangulo[][2] = {{0, 1}, {1, 2}, {2, 0}};
    const int cuadrado[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
    const int bosque[][2] = {{0, 1}, {1, 2}, {3, 4}, {4, 5}};
    const int cicloOtraComponente[][2] = {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {5, 3}};
    const int dosRutas[][2] = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    const int lazo[][2] = {{0, 0}};

    int aprobados = 0;
    aprobados += probarCaso("01. Grafo vacio", 0, nullptr, 0, false, representacion);
    aprobados += probarCaso("02. Vertices aislados", 4, nullptr, 0, false, representacion);
    aprobados += probarCaso("03. Una arista: volver al padre no es ciclo", 2,
                            unaArista, 1, false, representacion);
    aprobados += probarCaso("04. Arbol", 6, arbol, 5, false, representacion);
    aprobados += probarCaso("05. Triangulo", 3, triangulo, 3, true, representacion);
    aprobados += probarCaso("06. Cuadrado", 4, cuadrado, 4, true, representacion);
    aprobados += probarCaso("07. Componentes desconectadas sin ciclos", 7,
                            bosque, 4, false, representacion);
    aprobados += probarCaso("08. Ciclo en una componente que no contiene al 0", 7,
                            cicloOtraComponente, 5, true, representacion);
    aprobados += probarCaso("09. Dos rutas hacia un mismo vertice", 4,
                            dosRutas, 4, true, representacion);
    aprobados += probarCaso("10. Lazo en un vertice", 1, lazo, 1, true, representacion);
    return aprobados;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "=== LISTAS DE ADYACENCIA ===\n";
    int aprobados = probarRepresentacion(RepresentacionGrafo::LISTA_ADYACENCIA);

    std::cout << "\n=== MATRIZ DE ADYACENCIA ===\n";
    aprobados += probarRepresentacion(RepresentacionGrafo::MATRIZ_ADYACENCIA);

    std::cout << "\nPruebas aprobadas: " << aprobados << "/20\n";
    return aprobados == 20 ? 0 : 1;
}
