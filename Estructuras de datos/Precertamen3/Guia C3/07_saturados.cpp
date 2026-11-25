// Guía C3 · Ejercicio 07
// Escribe en salida los vértices con grado de entrada mayor que el de salida y
// retorna la cantidad. Orden libre, capacidad G.nVertex(). Usa O(V+E).
// Prepara también la justificación que solicita la guía.

#include <iostream>
#include "tGrafo.hpp"
#include "tCola.hpp"
#include <algorithm>
#include <vector>

namespace {
bool pendiente = false;
}

// TODO: desarrolla el ejercicio aquí. Elimina la marca pendiente al resolverlo.
int saturados(tGrafo& G, tVertice salida[]) {

    // supongo que hare un bfs, donde tendre 2 arreglos, en uno guardare la cantidad de arcos que salen y en el otro los que entran.
    tCola cola;
    int cuantos = 1;
    int n = G.nVertex();
    if (n == 0) return 0;
    tVertice w = 0;
    tVertice y;
    cola.enqueue(w);
    G.setMark(w, VISITADO);
    int* entrantes = new int[n](); 
    int* salientes = new int[n]();
    while (cola.size()){
        y = cola.frontValue(), cola.dequeue();
        for (w = G.first(y); w != n; w = G.next(y, w)){
            entrantes[w]++;
            salientes[y]++;
            if (G.getMark(w) == NOVISITADO){
                cola.enqueue(w), G.setMark(w, VISITADO), cuantos++;
            }
        }
        if (!cola.size() && cuantos < n)
            for (int p = 0; p < n ; p++)
                if (G.getMark(p) == NOVISITADO)
                    cola.enqueue(p), G.setMark(p, VISITADO), cuantos++;
    }
    int sobrecargados = 0;
    for(int i = 0; i < n; i++){
        G.setMark(i, NOVISITADO);
        if (salientes[i]-entrantes[i] < 0) 
            salida[sobrecargados++] = i;
    }
    delete[] salientes;
    delete[] entrantes;
    return sobrecargados;
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
    tGrafo g(5);
    g.setEdge(0,2,1); g.setEdge(1,2,1); g.setEdge(2,3,1); g.setEdge(4,3,1);
    int salida[5] = {};
    int n = saturados(g,salida);
    pruebaLista("Dos vértices saturados",salida,n,{2,3},5);
    tGrafo balanceado(2,false);
    balanceado.setEdge(0,1,1);
    n = saturados(balanceado,salida);
    pruebaLista("Grados iguales",salida,n,{},5);
    return errores == 0 ? 0 : 1;
}
