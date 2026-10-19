#ifndef ABB_HPP
#define ABB_HPP

// Basado en "05 Arboles EDD 2025-1.pdf", seccion ABB.
typedef int tipoElem;

// En las clases se llama tNodoArbolBin; aqui usamos el nombre del enunciado.
struct tNodo {
    tipoElem info;
    tNodo* izq;
    tNodo* der;
};

class tABB {
private:
    tNodo* raiz;
    int nElems;
    static void clearHelp(tNodo* nodo);
    static void inOrdenHelp(tNodo* nodo);
    static void preOrdenHelp(tNodo* nodo);
    static void postOrdenHelp(tNodo* nodo);

public:
    tABB();
    ~tABB();
    // El arbol es propietario de sus nodos. Usar referencias para pasarlo.
    tABB(const tABB&) = delete;
    tABB& operator=(const tABB&) = delete;

    void clear();
    void insert(tipoElem item); // Ignora duplicados, como en las clases.
    void remove(tipoElem item);
    int find(tipoElem item) const; // 1 si existe; 0 en caso contrario.
    int size() const;
    void inOrden() const;
    void preOrden() const;
    void postOrden() const;

    // Acceso agregado para llamar al algoritmo solicitado en el ejercicio.
    // No liberar sus nodos desde fuera del TDA.
    tNodo* getRaiz() const;
};

#endif
