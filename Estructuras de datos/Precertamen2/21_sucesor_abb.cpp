 #include <iostream>
#include "ABB.hpp"
#include "Pila.hpp"
#include "Cola.hpp"

/*
Pregunta 21: successor.
Reutiliza tus TDA originales de enteros, sin modificar sus typedef.
tNodo viene de ABB.hpp: info, izq y der.
No incluyas archivos .cpp desde este archivo.

Contrato:
- Recibe la raiz de un ABB y un entero positivo x.
- x siempre pertenece al arbol.
- Retorna el sucesor de x (menor elemento estrictamente mayor que x).
- Retorna -1 cuando x no tiene sucesor.
- Imprime en forma ascendente los potenciales sucesores, segun el enunciado.
- Tiempo requerido: O(h), donde h es la altura del arbol.
- No modificar ni liberar los nodos del arbol.

Operaciones disponibles si decides usarlas:
tPila: push, topValue, pop, size, clear.
tCola: enqueue, frontValue, dequeue, size, clear.
Consultar o eliminar requiere size() > 0.
pop y dequeue no retornan valores.

ATENCION A LA REDACCION DEL PDF:
El texto dice "descarto", pero para x=20 incluye al propio sucesor 21.
Los tres resultados de potenciales del main estan transcritos del PDF.
No se ha inventado una regla adicional para producirlos.
*/
int successor(tNodo* raiz, int x) {

    // buscare x, ire metiendo todo en una pila y sacare eel ultimo elemento, sera el sucesor mas cercano
    tNodo* aux = raiz; //parto recorriendo desde la raiz
    tPila camino;
    int sig = x + 1;
    while (aux != nullptr && aux->info != sig){
        if (aux->info > sig) {camino.push(aux->info);}
        if (sig > aux->info){
            aux = aux->der;
        }
        else if (sig < aux->info){
            aux = aux->izq;
        }
    }
    if (aux != nullptr && aux->info == sig ) {camino.push(sig);}
    // en este punto ya deberia haber encontrado sig
    // en la pila tendre el camino recorrido
    // metere en una cola todo
    tCola potenciales;
    while (camino.size()){ 
        potenciales.enqueue(camino.topValue());
        camino.pop();
    }
    if (!potenciales.size()) {return -1;}
    int encontrado = potenciales.frontValue();
    potenciales.dequeue();
    while (potenciales.size()){
        std::cout << potenciales.frontValue() << ' ';
        potenciales.dequeue();
    }
    return encontrado;
}

// Infraestructura de pruebas: no necesitas modificarla.
void probar(const char* nombre, tNodo* raiz, int x,
            int sucesorEsperado, const char* potencialesEsperados) {
    std::cout << nombre << "\nx = " << x
              << "\nTu output - potenciales: ";
    int obtenido = successor(raiz, x);
    std::cout << "\nTu output - sucesor:     " << obtenido
              << "\nEsperado  - potenciales: " << potencialesEsperados
              << "\nEsperado  - sucesor:     " << sucesorEsperado
              << "\n\n";
}

int main() {
    // Arbol de la figura 4:
    // 15: izquierdo 9, derecho 20.
    // 9: izquierdo 7, derecho 12.
    // 20: izquierdo 19, derecho 25.
    // 19: izquierdo 18.
    // 25: izquierdo 21.
    tNodo n7{7, nullptr, nullptr}, n12{12, nullptr, nullptr};
    tNodo n18{18, nullptr, nullptr}, n21{21, nullptr, nullptr};
    tNodo n19{19, &n18, nullptr}, n25{25, &n21, nullptr};
    tNodo n9{9, &n7, &n12}, n20{20, &n19, &n25};
    tNodo n15{15, &n9, &n20};

    // Tres ejemplos del PDF, conservados tal como aparecen.
    probar("1. Ejemplo del PDF", &n15, 12, 15, "(ninguno)");
    probar("2. Ejemplo del PDF", &n15, 20, 21, "25");
    probar("3. Ejemplo del PDF", &n15, 7, 9, "15");

    // Caso limite propio: unico nodo, sin sucesor.
    tNodo unico{42, nullptr, nullptr};
    probar("4. Caso adicional: solo raiz", &unico, 42, -1, "(ninguno)");

    // "(ninguno)" es una etiqueta explicativa del main.
    // Cuando no hay potenciales basta con no imprimir enteros.
    return 0;
}

