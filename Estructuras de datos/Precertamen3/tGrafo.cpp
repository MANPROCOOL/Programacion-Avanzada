#include "tGrafo.hpp"
#include <limits>
#include <stdexcept>
#include <utility>

namespace {
int validarCantidad(int n) {
    if (n < 0) throw std::invalid_argument("Cantidad de vertices negativa");
    return n;
}
}

tGrafo::tGrafo(int n)
    : tGrafo(n, true, RepresentacionGrafo::LISTA_ADYACENCIA) {}

tGrafo::tGrafo(int n, bool dirigido, RepresentacionGrafo representacion)
    : n_(validarCantidad(n)), dirigido_(dirigido), representacion_(representacion),
      arcos_(0), marcas_(nullptr), cabezas_(nullptr), cursores_(nullptr),
      pesos_(nullptr), existe_(nullptr) {
    try {
        marcas_ = new int[n_];
        for (int i = 0; i < n_; ++i) marcas_[i] = NOVISITADO;
        if (representacion_ == RepresentacionGrafo::LISTA_ADYACENCIA) {
            cabezas_ = new Arco*[n_]();
            cursores_ = new Arco*[n_]();
        } else if (representacion_ == RepresentacionGrafo::MATRIZ_ADYACENCIA) {
            const std::size_t nGrande = static_cast<std::size_t>(n_);
            if (nGrande != 0 && nGrande > std::numeric_limits<std::size_t>::max() / nGrande)
                throw std::length_error("Matriz demasiado grande");
            const std::size_t celdas = nGrande * nGrande;
            pesos_ = new int[celdas]();
            existe_ = new bool[celdas]();
        } else {
            throw std::invalid_argument("Representacion desconocida");
        }
    } catch (...) {
        liberar();
        throw;
    }
}

tGrafo::~tGrafo() { liberar(); }

void tGrafo::liberar() {
    if (cabezas_ != nullptr) {
        for (int v = 0; v < n_; ++v) {
            Arco* actual = cabezas_[v];
            while (actual != nullptr) {
                Arco* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            }
        }
    }
    delete[] cabezas_;
    delete[] cursores_;
    delete[] marcas_;
    delete[] pesos_;
    delete[] existe_;
    cabezas_ = nullptr;
    cursores_ = nullptr;
    marcas_ = nullptr;
    pesos_ = nullptr;
    existe_ = nullptr;
}

tGrafo::tGrafo(const tGrafo& otro)
    : tGrafo(otro.n_, otro.dirigido_, otro.representacion_) {
    // Si falla una reserva en este cuerpo, C++ destruye el objeto ya construido
    // por el constructor delegado y libera las listas copiadas parcialmente.
    for (int i = 0; i < n_; ++i) marcas_[i] = otro.marcas_[i];
    if (representacion_ == RepresentacionGrafo::LISTA_ADYACENCIA) {
        for (int v = 0; v < n_; ++v) {
            Arco** enlace = &cabezas_[v];
            for (Arco* a = otro.cabezas_[v]; a != nullptr; a = a->siguiente) {
                *enlace = new Arco{a->destino, a->peso, nullptr};
                enlace = &(*enlace)->siguiente;
            }
        }
    } else {
        const std::size_t celdas = static_cast<std::size_t>(n_) * n_;
        for (std::size_t i = 0; i < celdas; ++i) {
            pesos_[i] = otro.pesos_[i];
            existe_[i] = otro.existe_[i];
        }
    }
    arcos_ = otro.arcos_;
}

void tGrafo::intercambiar(tGrafo& otro) {
    std::swap(n_, otro.n_);
    std::swap(dirigido_, otro.dirigido_);
    std::swap(representacion_, otro.representacion_);
    std::swap(arcos_, otro.arcos_);
    std::swap(marcas_, otro.marcas_);
    std::swap(cabezas_, otro.cabezas_);
    std::swap(cursores_, otro.cursores_);
    std::swap(pesos_, otro.pesos_);
    std::swap(existe_, otro.existe_);
}

tGrafo& tGrafo::operator=(const tGrafo& otro) {
    if (this != &otro) {
        tGrafo copia(otro);
        intercambiar(copia);
    }
    return *this;
}

void tGrafo::validarVertice(tVertice v) const {
    if (v < 0 || v >= n_) throw std::out_of_range("Vertice fuera de 0..n-1");
}

std::size_t tGrafo::indice(tVertice v1, tVertice v2) const {
    return static_cast<std::size_t>(v1) * n_ + v2;
}

int tGrafo::nVertex() { return n_; }
int tGrafo::nEdges() { return arcos_; }

tVertice tGrafo::first(tVertice v) {
    validarVertice(v);
    if (representacion_ == RepresentacionGrafo::LISTA_ADYACENCIA) {
        cursores_[v] = cabezas_[v];
        return cursores_[v] == nullptr ? n_ : cursores_[v]->destino;
    }
    for (tVertice w = 0; w < n_; ++w)
        if (existe_[indice(v, w)]) return w;
    return n_;
}

tVertice tGrafo::next(tVertice v, tVertice w) {
    validarVertice(v);
    if (w < -1 || w > n_) throw std::out_of_range("Vecino fuera de -1..n");
    if (w == n_) return n_;
    if (representacion_ == RepresentacionGrafo::LISTA_ADYACENCIA) {
        Arco*& cursor = cursores_[v];
        if (cursor != nullptr && cursor->destino == w) {
            cursor = cursor->siguiente;
        } else {
            cursor = cabezas_[v];
            while (cursor != nullptr && cursor->destino <= w) cursor = cursor->siguiente;
        }
        return cursor == nullptr ? n_ : cursor->destino;
    }
    for (tVertice z = w + 1; z < n_; ++z)
        if (existe_[indice(v, z)]) return z;
    return n_;
}

void tGrafo::escribirArco(tVertice v1, tVertice v2, int peso) {
    if (representacion_ == RepresentacionGrafo::MATRIZ_ADYACENCIA) {
        existe_[indice(v1, v2)] = true;
        pesos_[indice(v1, v2)] = peso;
        return;
    }
    cursores_[v1] = nullptr;
    Arco** enlace = &cabezas_[v1];
    while (*enlace != nullptr && (*enlace)->destino < v2)
        enlace = &(*enlace)->siguiente;
    if (*enlace != nullptr && (*enlace)->destino == v2) (*enlace)->peso = peso;
    else *enlace = new Arco{v2, peso, *enlace};
}

void tGrafo::setEdge(tVertice v1, tVertice v2, int peso) {
    validarVertice(v1);
    validarVertice(v2);
    const bool nuevo = !isEdge(v1, v2);
    escribirArco(v1, v2, peso);
    if (!dirigido_ && v1 != v2) {
        try { escribirArco(v2, v1, peso); }
        catch (...) {
            if (nuevo) borrarArco(v1, v2); // No dejar media arista si falla new.
            throw;
        }
    }
    if (nuevo) ++arcos_;
}

void tGrafo::borrarArco(tVertice v1, tVertice v2) {
    if (representacion_ == RepresentacionGrafo::MATRIZ_ADYACENCIA) {
        existe_[indice(v1, v2)] = false;
        pesos_[indice(v1, v2)] = 0;
        return;
    }
    cursores_[v1] = nullptr;
    Arco** enlace = &cabezas_[v1];
    while (*enlace != nullptr && (*enlace)->destino < v2)
        enlace = &(*enlace)->siguiente;
    if (*enlace != nullptr && (*enlace)->destino == v2) {
        Arco* eliminado = *enlace;
        *enlace = eliminado->siguiente;
        delete eliminado;
    }
}

void tGrafo::deleteEdge(tVertice v1, tVertice v2) {
    validarVertice(v1);
    validarVertice(v2);
    if (!isEdge(v1, v2)) return;
    borrarArco(v1, v2);
    if (!dirigido_ && v1 != v2) borrarArco(v2, v1);
    --arcos_;
}

int tGrafo::isEdge(tVertice v1, tVertice v2) {
    validarVertice(v1);
    validarVertice(v2);
    if (representacion_ == RepresentacionGrafo::MATRIZ_ADYACENCIA)
        return existe_[indice(v1, v2)] ? 1 : 0;
    if (cursores_[v1] != nullptr && cursores_[v1]->destino == v2) return 1;
    Arco* a = cabezas_[v1];
    while (a != nullptr && a->destino < v2) a = a->siguiente;
    return a != nullptr && a->destino == v2 ? 1 : 0;
}

int tGrafo::weight(tVertice v1, tVertice v2) {
    validarVertice(v1);
    validarVertice(v2);
    if (representacion_ == RepresentacionGrafo::MATRIZ_ADYACENCIA)
        return existe_[indice(v1, v2)] ? pesos_[indice(v1, v2)] : 0;
    // En los bucles de la PPT, el vecino actual se consulta en O(1).
    if (cursores_[v1] != nullptr && cursores_[v1]->destino == v2)
        return cursores_[v1]->peso;
    Arco* a = cabezas_[v1];
    while (a != nullptr && a->destino < v2) a = a->siguiente;
    return a != nullptr && a->destino == v2 ? a->peso : 0;
}

int tGrafo::getMark(tVertice v) { validarVertice(v); return marcas_[v]; }
void tGrafo::setMark(tVertice v, int marca) { validarVertice(v); marcas_[v] = marca; }
