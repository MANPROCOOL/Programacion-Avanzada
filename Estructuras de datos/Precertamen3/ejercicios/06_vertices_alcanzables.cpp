/*
EJERCICIO 06 - VERTICES ALCANZABLES (G1)

Implementa contarAlcanzables(G, s). Debe retornar la cantidad de
vertices alcanzables desde s, incluyendo a s.

- El grafo puede ser dirigido o no dirigido. Respeta el sentido de los arcos.
- Puede haber ciclos, autolazos y vertices aislados.
- Usa getMark/setMark con NOVISITADO y VISITADO.
- El main reutiliza el mismo grafo para todas las consultas. La funcion debe
  preparar las marcas en cada llamada.
- Usa solo la interfaz publica de tGrafo. Puedes usar tCola o un auxiliar
  recursivo. Complejidad esperada con listas de adyacencia: O(V + E) por llamada.

Compilar desde Precertamen3:
g++ -std=c++11 -Wall -Wextra -Wpedantic ejercicios/06_vertices_alcanzables.cpp tGrafo.cpp tCola.cpp -o alcanzables
./alcanzables
*/

#include "../tGrafo.hpp"
#include "../tCola.hpp"
#include <iostream>

int DFS(tGrafo& G, tVertice v) {
    tVertice w;
	int cantidad = 1;
    G.setMark(v, VISITADO);
    for (w = G.first(v); w < G.nVertex(); w = G.next(v, w))
        if (G.getMark(w) == NOVISITADO)
            cantidad += DFS(G, w);
    return cantidad;
}

int BFS(tGrafo& G, tVertice v) {
 	tCola Q;
 	tVertice w, z;
 	Q.enqueue(v);
 	G.setMark(v, VISITADO);
	int cantidad = 1;
 	while (Q.size() != 0) {
 		z = Q.frontValue(); Q.dequeue();
 		for (w = G.first(z); w < G.nVertex(); w = G.next(z, w))
 			if (G.getMark(w) == NOVISITADO) {
 				G.setMark(w, VISITADO);
 				Q.enqueue(w);
				cantidad++;
 			}
 	}
	return cantidad;
}


int contarAlcanzables(tGrafo& G, tVertice v){

	int retorno = BFS(G, v);
	for (int i = 0; i < G.nVertex(); i++)
		G.setMark(i, NOVISITADO);
	return retorno;
}

bool probarCaso(const char* nombre, int obtenido, int esperado) {
    bool correcto = obtenido == esperado;
    std::cout << nombre << '\n'
              << "  Mi resultado: " << obtenido
              << " | Esperado: " << esperado
              << (correcto ? " [OK]\n" : " [ERROR]\n");
    return correcto;
}

int main() {
    int errores = 0;

    tGrafo ciclo(4, true);
    ciclo.setEdge(0, 1, 1);
    ciclo.setEdge(1, 2, 1);
    ciclo.setEdge(2, 0, 1);
    ciclo.setEdge(2, 3, 1);

    if (!probarCaso("Ciclo dirigido: desde 0",
                    contarAlcanzables(ciclo, 0), 4)) errores++;
    if (!probarCaso("Ciclo dirigido: desde 3, sin arcos de salida",
                    contarAlcanzables(ciclo, 3), 1)) errores++;
    if (!probarCaso("Ciclo dirigido: repetir desde 0 en el mismo grafo",
                    contarAlcanzables(ciclo, 0), 4)) errores++;

    tGrafo ramas(4, true);
    ramas.setEdge(0, 1, 1);
    ramas.setEdge(0, 2, 1);
    ramas.setEdge(2, 3, 1);

    if (!probarCaso("Grafo dirigido: dos ramas desde 0",
                    contarAlcanzables(ramas, 0), 4)) errores++;

    tGrafo noDirigido(4, false);
    noDirigido.setEdge(0, 1, 1);
    noDirigido.setEdge(1, 2, 1);

    if (!probarCaso("Grafo no dirigido: desde 2",
                    contarAlcanzables(noDirigido, 2), 3)) errores++;
    if (!probarCaso("Grafo no dirigido: desde el vertice aislado 3",
                    contarAlcanzables(noDirigido, 3), 1)) errores++;

    tGrafo conAutolazo(2, true);
    conAutolazo.setEdge(0, 0, 1);
    conAutolazo.setEdge(0, 1, 1);

    if (!probarCaso("Autolazo: el origen se cuenta una sola vez",
                    contarAlcanzables(conAutolazo, 0), 2)) errores++;

    std::cout << "\n" << 7 - errores << " / 7 casos correctos\n";
    return errores == 0 ? 0 : 1;
}