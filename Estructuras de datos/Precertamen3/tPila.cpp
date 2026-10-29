#include "tPila.hpp"
#include <stdexcept>
#include <utility>

tPila::tPila() : tope_(nullptr), cantidad_(0) {}
tPila::~tPila() { clear(); }

tPila::tPila(const tPila& otra) : tPila() {
    Nodo** enlace = &tope_;
    for (Nodo* actual = otra.tope_; actual != nullptr; actual = actual->siguiente) {
        *enlace = new Nodo{actual->valor, nullptr};
        enlace = &(*enlace)->siguiente;
        ++cantidad_;
    }
}

tPila& tPila::operator=(const tPila& otra) {
    if (this != &otra) {
        tPila copia(otra);
        std::swap(tope_, copia.tope_);
        std::swap(cantidad_, copia.cantidad_);
    }
    return *this;
}

void tPila::push(tVertice valor) {
    tope_ = new Nodo{valor, tope_};
    ++cantidad_;
}

void tPila::pop() {
    if (isEmpty()) throw std::underflow_error("Pila vacia");
    Nodo* eliminado = tope_;
    tope_ = tope_->siguiente;
    delete eliminado;
    --cantidad_;
}

tVertice tPila::topValue() const {
    if (isEmpty()) throw std::underflow_error("Pila vacia");
    return tope_->valor;
}

int tPila::size() const { return cantidad_; }
bool tPila::isEmpty() const { return cantidad_ == 0; }
void tPila::clear() {
    while (tope_ != nullptr) {
        Nodo* eliminado = tope_;
        tope_ = tope_->siguiente;
        delete eliminado;
    }
    cantidad_ = 0;
}
