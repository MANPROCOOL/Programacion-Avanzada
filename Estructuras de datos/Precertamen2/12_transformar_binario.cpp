#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include "Pila.hpp"

// Ejercicio 12: transformar un entero positivo a una lista de bits.
// Usa tu Pila.hpp / Pila.cpp ORIGINAL de enteros, sin modificar sus typedef.
// tLista se incluye aqui con las operaciones de las clases.
// No incluyas atender_clientes.cpp: solo se reutiliza aqui el TDA lista.

typedef int tElemLista;

// Lista enlazada con cursor (posiciones de 0 a length()).
// Admite enteros repetidos (por ejemplo, varios bits iguales).
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
    tLista() : cabeza(new NodoLista{0, nullptr}), fin(cabeza),
               actual(cabeza), tam(0), posicion(0) {}

    // Copia profunda: cada lista conserva sus propios enlaces.
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

/*
Contrato:
- decimal > 0 (el cero y los negativos no forman parte del enunciado).
- Usar una pila de numeros enteros.
- Retornar una tLista de enteros: cada elemento debe ser 0 o 1.
- La lista se lee desde el bit mas significativo al menos significativo.
- Ejemplo: transformar(29) retorna la lista [1, 1, 1, 0, 1].
- No basta con imprimir el resultado: hay que retornar la lista.

Operaciones de tu pila:
  restos.push(entero); restos.topValue(); restos.pop(); restos.size();
  topValue y pop requieren que la pila no este vacia.

Operaciones principales de la lista:
  resultado.append(entero); resultado.length();
  moveToStart(); next(); currPos(); getValue();
  getValue requiere que currPos() < length().
*/
tLista transformar(unsigned int decimal) {

    tPila restos;
    tLista resultado;
    while (decimal != 1 && decimal){
        restos.push(decimal%2);
        decimal = decimal/2;
    }
    restos.push(decimal);
    while (restos.size()){
        resultado.append(restos.topValue());
        restos.pop();
    }

    return resultado;

}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(unsigned int decimal, const std::string& esperado) {
    std::cout << "Decimal: " << decimal << "\nTu output: ";
    tLista binario = transformar(decimal);

    if (binario.length() == 0) {
        std::cout << "PENDIENTE (lista vacia)";
    } else {
        for (binario.moveToStart(); binario.currPos() < binario.length();
             binario.next()) {
            std::cout << binario.getValue() << ' ';
        }
    }

    std::cout << "\nEsperado:  ";
    for (char bit : esperado) std::cout << bit << ' ';
    std::cout << "\n\n";
}

int main() {
    // Ejemplo del PDF:
    probar(29u, "11101");

    // Casos adicionales propios: todos son enteros positivos.
    probar(1u, "1");
    probar(2u, "10");
    probar(3u, "11");
    probar(4u, "100");
    probar(7u, "111");
    probar(8u, "1000");
    probar(10u, "1010");
    probar(32u, "100000");
    probar(255u, "11111111");
    probar(256u, "100000000");
    probar(1024u, "10000000000");

    // Maximo unsigned int: tantos unos como bits de valor tenga el tipo.
    probar(std::numeric_limits<unsigned int>::max(),
           std::string(std::numeric_limits<unsigned int>::digits, '1'));
    return 0;
}
