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

    // ===== INICIO DE TU TRABAJO =====
    // Implementa aqui el algoritmo.
    // No declares otras variables, contadores ni estructuras auxiliares.
    // No uses recursion para almacenar elementos en la pila de llamadas.
    // Usa directamente topValue() o frontValue() para transferir valores con push() o enqueue().
    // Comprueba size() > 0 antes de acceder o quitar un elemento.

    // ===== FIN DE TU TRABAJO =====
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
