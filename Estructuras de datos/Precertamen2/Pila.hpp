#ifndef PILA_HPP
#define PILA_HPP

// Interfaz basada en "04 Listas, Pilas y Colas.pdf".
// Implementacion con nodos enlazados para enteros.
typedef int tElemPila;

class tPila {
private:
    struct tNodo {
        tElemPila info;
        tNodo* sig;
    };

    tNodo* tope;
    int tam;

public:
    tPila();
    ~tPila();

    // Evita compartir nodos accidentalmente. Recibir por referencia.
    tPila(const tPila&) = delete;
    tPila& operator=(const tPila&) = delete;

    // Consultar y eliminar requiere size() > 0.
    // Insertar retorna 1; eliminar no retorna un valor.
    int push(tElemPila item);
    void pop();
    tElemPila topValue() const;
    int size() const;
    void clear();
};

#endif
