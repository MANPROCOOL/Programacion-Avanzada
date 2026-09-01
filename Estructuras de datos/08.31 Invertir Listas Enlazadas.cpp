#include <iostream>
#include <string>
#include "ListaEnlazada.hpp"

// Función auxiliar para imprimir el contenido de la lista en orden
void imprimirLista(tLista& lista) {
    lista.moveToStart();
    for (unsigned int i = 0; i < lista.length(); i++) {
        std::cout << lista.getValue();
        lista.next();
    }
    std::cout << std::endl;
}

int main() {
    tLista lista;
    std::string palabra;

    std::cout << "Ingresa una palabra: ";
    std::cin >> palabra;

    // Insertar cada caracter de la palabra en la lista
    for (char c : palabra) {
        lista.append(c);
    }

    std::cout << "\nPalabra original en la lista: ";
    imprimirLista(lista);

    // Invertir la lista con el metodo "invertirforma1"
    lista.invertirforma1();

    std::cout << "Palabra invertida con invertirforma1: ";
    imprimirLista(lista);

    return 0;
}