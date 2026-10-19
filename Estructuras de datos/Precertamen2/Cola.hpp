#ifndef COLA_HPP
#define COLA_HPP

// Interfaz basada en "04 Listas, Pilas y Colas.pdf".
// Implementacion con nodos enlazados para enteros.
typedef int tElemCola;

class tCola {
private:
    struct tNodo {
        tElemCola info;
        tNodo* sig;
    };

    tNodo* frente;
    tNodo* fin;
    int tam;

public:
    tCola();
    ~tCola();

    // Evita compartir nodos accidentalmente. Recibir por referencia.
    tCola(const tCola&) = delete;
    tCola& operator=(const tCola&) = delete;

    // Consultar y eliminar requiere size() > 0.
    // Insertar retorna 1; eliminar no retorna un valor.
    int enqueue(tElemCola item);
    void dequeue();
    tElemCola frontValue() const;
    int size() const;
    void clear();
};

#endif
