#include <iostream>
#include "Pila.hpp"
#include "Cola.hpp"

using namespace std;

// A: ascendente desde el tope hacia la base.
// B: descendente desde el tope hacia la base.
// C: inicialmente vacia; debe quedar descendente desde el tope a la base.
// Se permite consumir A y B. No se exige conservarlas.
void merge(tPila& A, tPila& B, tPila& C) {
    tCola auxiliar;  // Unica estructura auxiliar permitida.
    // La pila A esta ascendente de tope a base, tengo que sacar y meter a C
    // El problema es la pila B, Esta al revez, tengo que darla vuelta
    while (B.size()){
        auxiliar.enqueue(B.topValue());
        B.pop();
    }
    while (auxiliar.size()){
        B.push(auxiliar.frontValue());
        auxiliar.dequeue();
    }
    while(A.size() && B.size()){
        if (A.topValue() < B.topValue()){
            C.push(A.topValue());
            A.pop();
        }
        else if (B.topValue() < A.topValue()){
            C.push(B.topValue());
            B.pop();
        }
        else {
            C.push(A.topValue());
            C.push(B.topValue());
            A.pop();
            B.pop();      
        }
    }
    if (!B.size()){
        while(A.size()){
            C.push(A.topValue());
            A.pop();   
        }
    }
    else if (!A.size()){
        while(B.size()){
            C.push(B.topValue());
            B.pop();   
        }
    }
    
}

int main() {
    tPila A;
    tPila B;
    tPila C;

    // Datos de prueba. El ultimo valor insertado queda en el tope.
    A.push(7);
    A.push(4);
    A.push(1);  // A, del tope a la base: 1, 4, 7.

    B.push(2);
    B.push(5);
    B.push(8);  // B, del tope a la base: 8, 5, 2.

    merge(A, B, C);

    cout << "C (del tope a la base): ";
    // Mostrar C consume sus elementos, para no necesitar una copia.
    while (C.size() > 0) {
        cout << C.topValue() << ' ';
        C.pop();
    }
    cout << '\n';
    cout << "Resultado esperado: 8 7 5 4 2 1\n";

    return 0;
}
