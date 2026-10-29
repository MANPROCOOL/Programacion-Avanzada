#ifndef TDAS_CLASE08_TGRAFO_HPP
#define TDAS_CLASE08_TGRAFO_HPP

#include "tTipos.hpp"
#include <cstddef>

// Extension: la PPT no fija como elegir direccion y representacion.
enum class RepresentacionGrafo { LISTA_ADYACENCIA, MATRIZ_ADYACENCIA };

class tGrafo {
public:
    // Constructor de la PPT: digrafo con listas de adyacencia ordenadas.
    tGrafo(int n);
    tGrafo(int n, bool dirigido,
           RepresentacionGrafo representacion = RepresentacionGrafo::LISTA_ADYACENCIA);
    ~tGrafo();
    tGrafo(const tGrafo& otro);
    tGrafo& operator=(const tGrafo& otro);

    // Firmas exactas de las diapositivas 28-30.
    int nVertex();
    int nEdges();
    tVertice first(tVertice v);
    tVertice next(tVertice v, tVertice w);
    void setEdge(tVertice v1, tVertice v2, int peso);
    void deleteEdge(tVertice v1, tVertice v2);
    int isEdge(tVertice v1, tVertice v2);
    int weight(tVertice v1, tVertice v2);
    int getMark(tVertice v);
    void setMark(tVertice v, int marca);

private:
    struct Arco {
        tVertice destino;
        int peso;
        Arco* siguiente;
    };
    int n_;
    bool dirigido_;
    RepresentacionGrafo representacion_;
    int arcos_;
    int* marcas_;
    // Solo la representacion elegida ocupa almacenamiento de aristas.
    Arco** cabezas_;
    Arco** cursores_; // Cursor por vertice para avanzar en O(1) con first/next.
    int* pesos_;     // Matriz linealizada, indice = origen*n + destino.
    bool* existe_;

    void validarVertice(tVertice v) const;
    std::size_t indice(tVertice v1, tVertice v2) const;
    void escribirArco(tVertice v1, tVertice v2, int peso);
    void borrarArco(tVertice v1, tVertice v2);
    void liberar();
    void intercambiar(tGrafo& otro);
};

#endif
