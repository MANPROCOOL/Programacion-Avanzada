#ifndef TDAS_CLASE08_TCONJUNTOSDISJUNTOS_HPP
#define TDAS_CLASE08_TCONJUNTOSDISJUNTOS_HPP

// Apoyo opcional para las clases de equivalencia de Kruskal (diapositiva 72).
// La PPT no desarrolla esta implementacion ni establece su interfaz.
class tConjuntosDisjuntos {
public:
    explicit tConjuntosDisjuntos(int n);
    ~tConjuntosDisjuntos();
    tConjuntosDisjuntos(const tConjuntosDisjuntos& otro);
    tConjuntosDisjuntos& operator=(const tConjuntosDisjuntos& otro);
    int find(int elemento);
    bool unite(int a, int b); // true si efectivamente unio dos componentes.
    bool connected(int a, int b);
    int count() const;

private:
    int n_;
    int* padre_;
    int* tamano_;
    int componentes_;
    void validar(int elemento) const;
};

#endif
