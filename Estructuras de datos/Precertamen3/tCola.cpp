#include "tCola.hpp"
#include <stdexcept>
#include <utility>

tCola::tCola() : frente_(nullptr), final_(nullptr), cantidad_(0) {}
tCola::~tCola() { clear(); }

tCola::tCola(const tCola& otra) : tCola() {
    for (Nodo* actual = otra.frente_; actual != nullptr; actual = actual->siguiente)
        enqueue(actual->valor);
}

tCola& tCola::operator=(const tCola& otra) {
    if (this != &otra) {
        tCola copia(otra);
        std::swap(frente_, copia.frente_);
        std::swap(final_, copia.final_);
        std::swap(cantidad_, copia.cantidad_);
    }
    return *this;
}

void tCola::enqueue(tVertice valor) {
    Nodo* nuevo = new Nodo{valor, nullptr};
    if (final_ != nullptr) final_->siguiente = nuevo;
    else frente_ = nuevo;
    final_ = nuevo;
    ++cantidad_;
}

void tCola::dequeue() {
    if (isEmpty()) throw std::underflow_error("Cola vacia");
    Nodo* eliminado = frente_;
    frente_ = frente_->siguiente;
    delete eliminado;
    --cantidad_;
    if (frente_ == nullptr) final_ = nullptr;
}

tVertice tCola::frontValue() const {
    if (isEmpty()) throw std::underflow_error("Cola vacia");
    return frente_->valor;
}

int tCola::size() const { return cantidad_; }
bool tCola::isEmpty() const { return cantidad_ == 0; }
void tCola::clear() {
    while (frente_ != nullptr) {
        Nodo* eliminado = frente_;
        frente_ = frente_->siguiente;
        delete eliminado;
    }
    final_ = nullptr;
    cantidad_ = 0;
}
