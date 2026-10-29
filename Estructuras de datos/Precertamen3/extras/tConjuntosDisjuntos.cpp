#include "tConjuntosDisjuntos.hpp"
#include <stdexcept>
#include <utility>

tConjuntosDisjuntos::tConjuntosDisjuntos(int n)
    : n_(n), padre_(nullptr), tamano_(nullptr), componentes_(n) {
    if (n < 0) throw std::invalid_argument("Cantidad de elementos negativa");
    try {
        padre_ = new int[n_];
        tamano_ = new int[n_];
    } catch (...) {
        delete[] padre_;
        throw;
    }
    for (int i = 0; i < n_; ++i) { padre_[i] = i; tamano_[i] = 1; }
}

tConjuntosDisjuntos::~tConjuntosDisjuntos() { delete[] padre_; delete[] tamano_; }

tConjuntosDisjuntos::tConjuntosDisjuntos(const tConjuntosDisjuntos& otro)
    : tConjuntosDisjuntos(otro.n_) {
    componentes_ = otro.componentes_;
    for (int i = 0; i < n_; ++i) { padre_[i] = otro.padre_[i]; tamano_[i] = otro.tamano_[i]; }
}

tConjuntosDisjuntos& tConjuntosDisjuntos::operator=(const tConjuntosDisjuntos& otro) {
    if (this != &otro) {
        tConjuntosDisjuntos copia(otro);
        std::swap(n_, copia.n_);
        std::swap(componentes_, copia.componentes_);
        std::swap(padre_, copia.padre_);
        std::swap(tamano_, copia.tamano_);
    }
    return *this;
}

void tConjuntosDisjuntos::validar(int elemento) const {
    if (elemento < 0 || elemento >= n_) throw std::out_of_range("Elemento fuera de 0..n-1");
}

int tConjuntosDisjuntos::find(int elemento) {
    validar(elemento);
    int raiz = elemento;
    while (padre_[raiz] != raiz) raiz = padre_[raiz];
    while (padre_[elemento] != elemento) {
        const int siguiente = padre_[elemento];
        padre_[elemento] = raiz;
        elemento = siguiente;
    }
    return raiz;
}

bool tConjuntosDisjuntos::unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (tamano_[a] < tamano_[b]) std::swap(a, b);
    padre_[b] = a;
    tamano_[a] += tamano_[b];
    --componentes_;
    return true;
}

bool tConjuntosDisjuntos::connected(int a, int b) { return find(a) == find(b); }
int tConjuntosDisjuntos::count() const { return componentes_; }
