#include <cassert>
#include <iostream>
#include <string>
#include <utility>

// TDA de apoyo basados en las operaciones de las clases.
// Tu cola de int no puede almacenar Cliente sin cambiar su tipo.
// Este archivo es independiente: no modifica ni incluye tus otros TDA.

typedef int tElemLista;

// Lista enlazada con cursor (posiciones de 0 a length()).
// Los productos unicos son una precondicion de los datos de entrada.
class tLista {
private:
    struct NodoLista {
        tElemLista info;
        NodoLista* sig;
    };
    NodoLista* cabeza; // Centinela.
    NodoLista* fin;
    NodoLista* actual; // Enlace anterior al elemento actual.
    int tam;
    int posicion;

public:
    tLista() : cabeza(new NodoLista{0, nullptr}), fin(cabeza), actual(cabeza), tam(0), posicion(0) {}

    // Copia profunda: cada Cliente conserva su propia lista.
    tLista(const tLista& otra) : tLista() {
        for (NodoLista* p = otra.cabeza->sig; p; p = p->sig)
            append(p->info);
        moveToPos(otra.posicion);
    }

    tLista& operator=(const tLista& otra) {
        if (this != &otra) {
            tLista copia(otra);
            std::swap(cabeza, copia.cabeza);
            std::swap(fin, copia.fin);
            std::swap(actual, copia.actual);
            std::swap(tam, copia.tam);
            std::swap(posicion, copia.posicion);
        }
        return *this;
    }

    ~tLista() { clear(); delete cabeza; }

    void clear() {
        while (cabeza->sig) {
            NodoLista* borrar = cabeza->sig;
            cabeza->sig = borrar->sig;
            delete borrar;
        }
        fin = actual = cabeza;
        tam = posicion = 0;
    }

    int insert(tElemLista item) {
        actual->sig = new NodoLista{item, actual->sig};
        if (fin == actual) fin = actual->sig;
        tam++;
        return 1;
    }

    int append(tElemLista item) {
        fin->sig = new NodoLista{item, nullptr};
        fin = fin->sig;
        tam++;
        return 1;
    }

    tElemLista erase() {
        assert(posicion < tam);
        NodoLista* borrar = actual->sig;
        tElemLista valor = borrar->info;
        actual->sig = borrar->sig;
        if (fin == borrar) fin = actual;
        delete borrar;
        tam--;
        return valor;
    }

    void moveToStart() { actual = cabeza; posicion = 0; }
    void moveToEnd() { actual = fin; posicion = tam; }

    void next() {
        if (posicion < tam) { actual = actual->sig; posicion++; }
    }

    void prev() {
        if (posicion == 0) return;
        NodoLista* anterior = cabeza;
        while (anterior->sig != actual) anterior = anterior->sig;
        actual = anterior;
        posicion--;
    }

    int length() const { return tam; }
    int currPos() const { return posicion; }

    void moveToPos(int pos) {
        assert(pos >= 0 && pos <= tam);
        moveToStart();
        while (posicion < pos) next();
    }

    tElemLista getValue() const {
        assert(posicion < tam);
        return actual->sig->info;
    }
};

struct Cliente {
    std::string rut;
    tLista listaProductos;
};

// Misma interfaz de tu cola, especializada para Cliente.
// frontValue consulta sin eliminar; dequeue elimina sin retornar.
// frontValue y dequeue requieren size() > 0.
class tColaClientes {
private:
    struct NodoCola {
        Cliente info;
        NodoCola* sig;
        explicit NodoCola(const Cliente& item) : info(item), sig(nullptr) {}
    };
    NodoCola* frente;
    NodoCola* fin;
    int tam;

public:
    tColaClientes() : frente(nullptr), fin(nullptr), tam(0) {}
    ~tColaClientes() { clear(); }
    tColaClientes(const tColaClientes&) = delete;
    tColaClientes& operator=(const tColaClientes&) = delete;

    int enqueue(const Cliente& item) {
        NodoCola* nuevo = new NodoCola(item);
        if (tam == 0) frente = nuevo;
        else fin->sig = nuevo;
        fin = nuevo;
        tam++;
        return 1;
    }

    Cliente frontValue() const {
        assert(tam > 0);
        return frente->info;
    }

    void dequeue() {
        assert(tam > 0);
        NodoCola* borrar = frente;
        frente = frente->sig;
        delete borrar;
        tam--;
        if (tam == 0) fin = nullptr;
    }

    int size() const { return tam; }

    void clear() {
        while (tam > 0) dequeue();
    }
};

/*
Recibes:
- clientes: cola FIFO de Cliente.
- cajeros: arreglo de cantidadCajas booleanos.
  true = ocupado, false = disponible.
- cantidadCajas: longitud del arreglo; se agrega porque el arreglo
  por si solo no comunica su longitud a la funcion.

Debes imprimir cada asignacion: i j
i = indice del cajero (desde 0).
j = indice de llegada del cliente (desde 0), como en el ejemplo.

El fragmento recibido NO define cuando se libera una caja ocupada,
el tiempo por producto ni si las asignaciones son simultaneas.
Consulta esa regla antes de validar una simulacion completa.
No hay una politica de tiempos implementada en el esqueleto.
*/
void atenderClientes(tColaClientes& clientes, bool cajeros[], int cantidadCajas) {

    

}

// Preparacion del ejemplo: no necesitas modificarla.
int main() {
    tColaClientes clientes;

    Cliente c0;
    c0.rut = "111-1";
    c0.listaProductos.append(1);
    c0.listaProductos.append(123);
    c0.listaProductos.append(9);
    clientes.enqueue(c0);

    Cliente c1;
    c1.rut = "222-2";
    c1.listaProductos.append(10);
    c1.listaProductos.append(4);
    c1.listaProductos.append(1);
    clientes.enqueue(c1);

    Cliente c2;
    c2.rut = "333-3";
    c2.listaProductos.append(10);
    clientes.enqueue(c2);

    Cliente c3;
    c3.rut = "555-5";
    c3.listaProductos.append(10);
    clientes.enqueue(c3);

    bool cajeros[] = {true, false, false, false};
    const int cantidadCajas = 4;

    std::cout << "Ejemplo del enunciado\nTu output:\n";
    atenderClientes(clientes, cajeros, cantidadCajas);

    // Transcripcion del resultado proporcionado, sin inventar sus tiempos.
    std::cout << "\nEsperado (segun el enunciado):\n"
              << "1 0\n"
              << "2 1\n"
              << "0 2\n"
              << "1 3\n";
    return 0;
}

