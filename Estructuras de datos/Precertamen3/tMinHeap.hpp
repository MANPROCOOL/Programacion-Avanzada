#ifndef TDAS_CLASE08_TMINHEAP_HPP
#define TDAS_CLASE08_TMINHEAP_HPP

struct tItemHeap {
    int id;        // Vertice o indice de una arista guardada por el ejercicio.
    int prioridad; // Distancia estimada o peso.
};

// Heap minimo indexado, IDs unicos en 0..capacidad-1. Sin contenedores STL.
// La PPT no fija nombres para sus operaciones.
class tMinHeap {
public:
    explicit tMinHeap(int capacidad);
    ~tMinHeap();
    tMinHeap(const tMinHeap& otro);
    tMinHeap& operator=(const tMinHeap& otro);
    void insert(int id, int prioridad);
    tItemHeap getMin() const;
    tItemHeap removeMin();
    void remove(int id);
    void updatePriority(int id, int nuevaPrioridad);
    bool contains(int id) const;
    int priority(int id) const;
    int size() const;
    bool isEmpty() const;
    void clear();

private:
    int capacidad_;
    int cantidad_;
    tItemHeap* heap_;
    int* posicion_; // -1 si el ID no esta en el heap.
    void validarId(int id) const;
    bool menor(int a, int b) const;
    void intercambiar(int a, int b);
    void intercambiarEstado(tMinHeap& otro);
    void subir(int i);
    void bajar(int i);
};

#endif
