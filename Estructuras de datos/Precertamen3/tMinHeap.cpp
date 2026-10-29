#include "tMinHeap.hpp"
#include <stdexcept>
#include <utility>

tMinHeap::tMinHeap(int capacidad)
    : capacidad_(capacidad), cantidad_(0), heap_(nullptr), posicion_(nullptr) {
    if (capacidad < 0) throw std::invalid_argument("Capacidad negativa");
    try {
        heap_ = new tItemHeap[capacidad_];
        posicion_ = new int[capacidad_];
    } catch (...) {
        delete[] heap_;
        throw;
    }
    for (int i = 0; i < capacidad_; ++i) posicion_[i] = -1;
}

tMinHeap::~tMinHeap() { delete[] heap_; delete[] posicion_; }

tMinHeap::tMinHeap(const tMinHeap& otro) : tMinHeap(otro.capacidad_) {
    cantidad_ = otro.cantidad_;
    for (int i = 0; i < cantidad_; ++i) heap_[i] = otro.heap_[i];
    for (int i = 0; i < capacidad_; ++i) posicion_[i] = otro.posicion_[i];
}

void tMinHeap::intercambiarEstado(tMinHeap& otro) {
    std::swap(capacidad_, otro.capacidad_);
    std::swap(cantidad_, otro.cantidad_);
    std::swap(heap_, otro.heap_);
    std::swap(posicion_, otro.posicion_);
}

tMinHeap& tMinHeap::operator=(const tMinHeap& otro) {
    if (this != &otro) {
        tMinHeap copia(otro);
        intercambiarEstado(copia);
    }
    return *this;
}

void tMinHeap::validarId(int id) const {
    if (id < 0 || id >= capacidad_) throw std::out_of_range("ID fuera de 0..capacidad-1");
}

bool tMinHeap::menor(int a, int b) const {
    if (heap_[a].prioridad != heap_[b].prioridad)
        return heap_[a].prioridad < heap_[b].prioridad;
    return heap_[a].id < heap_[b].id;
}

void tMinHeap::intercambiar(int a, int b) {
    std::swap(heap_[a], heap_[b]);
    posicion_[heap_[a].id] = a;
    posicion_[heap_[b].id] = b;
}

void tMinHeap::subir(int i) {
    while (i > 0) {
        const int padre = (i - 1) / 2;
        if (!menor(i, padre)) break;
        intercambiar(i, padre);
        i = padre;
    }
}

void tMinHeap::bajar(int i) {
    while (i < cantidad_ / 2) {
        int hijo = 2 * i + 1;
        if (hijo + 1 < cantidad_ && menor(hijo + 1, hijo)) ++hijo;
        if (!menor(hijo, i)) break;
        intercambiar(i, hijo);
        i = hijo;
    }
}

void tMinHeap::insert(int id, int prioridad) {
    validarId(id);
    if (posicion_[id] != -1) throw std::invalid_argument("ID duplicado en el heap");
    // Hay capacidad: a lo sumo capacidad_ IDs distintos pueden estar presentes.
    heap_[cantidad_] = tItemHeap{id, prioridad};
    posicion_[id] = cantidad_;
    ++cantidad_;
    subir(cantidad_ - 1);
}

tItemHeap tMinHeap::getMin() const {
    if (isEmpty()) throw std::underflow_error("Heap vacio");
    return heap_[0];
}

tItemHeap tMinHeap::removeMin() {
    const tItemHeap minimo = getMin();
    remove(minimo.id);
    return minimo;
}

void tMinHeap::remove(int id) {
    validarId(id);
    const int i = posicion_[id];
    if (i == -1) throw std::invalid_argument("ID ausente del heap");
    intercambiar(i, cantidad_ - 1);
    --cantidad_;
    posicion_[id] = -1;
    if (i < cantidad_) {
        if (i > 0 && menor(i, (i - 1) / 2)) subir(i);
        else bajar(i);
    }
}

void tMinHeap::updatePriority(int id, int nuevaPrioridad) {
    validarId(id);
    const int i = posicion_[id];
    if (i == -1) throw std::invalid_argument("ID ausente del heap");
    const int anterior = heap_[i].prioridad;
    heap_[i].prioridad = nuevaPrioridad;
    if (nuevaPrioridad < anterior) subir(i);
    else if (nuevaPrioridad > anterior) bajar(i);
}

bool tMinHeap::contains(int id) const { validarId(id); return posicion_[id] != -1; }
int tMinHeap::priority(int id) const {
    validarId(id);
    if (posicion_[id] == -1) throw std::invalid_argument("ID ausente del heap");
    return heap_[posicion_[id]].prioridad;
}
int tMinHeap::size() const { return cantidad_; }
bool tMinHeap::isEmpty() const { return cantidad_ == 0; }
void tMinHeap::clear() {
    cantidad_ = 0;
    for (int i = 0; i < capacidad_; ++i) posicion_[i] = -1;
}
