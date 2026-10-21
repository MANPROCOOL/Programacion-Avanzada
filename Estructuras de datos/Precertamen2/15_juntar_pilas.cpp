#include <iostream>
#include <initializer_list>
#include "Pila.hpp"
#include "Cola.hpp"

/*
Pregunta 15:
- INICIO esta ordenada descendentemente desde el tope hacia la base.
- FIN esta ordenada ascendentemente desde el tope hacia la base.
- Debes fusionarlas en TODO, ascendente desde el tope hacia la base.
- TODO llega vacia. Las pilas se reciben por referencia.
- Puedes consumir las pilas de entrada: no se exige conservarlas.
- Solo se permiten TDA pila y cola para las estructuras auxiliares.
- Esta pregunta NO impone el limite de una cola ni prohibe variables
  escalares como en la pregunta 1.

Usa tus TDA originales de enteros sin cambiar sus typedef.
Pila: push, topValue, pop, size, clear.
Cola: enqueue, frontValue, dequeue, size, clear.
Consultar o eliminar requiere size() > 0.
pop y dequeue no retornan un valor.
*/


void juntar(tPila& INICIO, tPila& FIN, tPila& TODO) {

    tCola aux;
    while(FIN.size()){ // paso la pila fin a mi cola auxiliar
        aux.enqueue(FIN.topValue());
        FIN.pop();
    }
    while (aux.size()){ // La devuelvo, ahora me queda comoda para trabajar
        FIN.push(aux.frontValue());
        aux.dequeue();
    }
    while (INICIO.size() && FIN.size()){
        if (INICIO.topValue() > FIN.topValue()){
            TODO.push(INICIO.topValue());
            INICIO.pop();
        }
        else {
            TODO.push(FIN.topValue());
            FIN.pop();
        }
    }
    while (INICIO.size()){
        TODO.push(INICIO.topValue());
        INICIO.pop();
    }
    while (FIN.size()){
        TODO.push(FIN.topValue());
        FIN.pop();
    }
}



// Preparacion de pruebas: no necesitas modificarla.
// Recibe los elementos escritos en orden TOPE -> BASE.
// initializer_list se usa solo para preparar datos, fuera del algoritmo.
void preparar(tPila& pila, std::initializer_list<int> topeABase) {
    tPila temporal;
    for (int pagina : topeABase) temporal.push(pagina);
    while (temporal.size() > 0) {
        pila.push(temporal.topValue());
        temporal.pop();
    }
}

void mostrar(tPila& pila) {
    if (pila.size() == 0) {
        std::cout << "[vacia]";
        return;
    }
    while (pila.size() > 0) {
        std::cout << pila.topValue() << ' ';
        pila.pop();
    }
}

void probar(const char* nombre, std::initializer_list<int> inicio, std::initializer_list<int> fin, const char* esperado) {
    tPila INICIO, FIN, TODO;
    preparar(INICIO, inicio);
    preparar(FIN, fin);

    std::cout << nombre << "\nINICIO (tope -> base): ";
    for (int pagina : inicio) std::cout << pagina << ' ';
    std::cout << "\nFIN    (tope -> base): ";
    for (int pagina : fin) std::cout << pagina << ' ';

    juntar(INICIO, FIN, TODO);
    std::cout << "\nTu output TODO (tope -> base): ";
    mostrar(TODO);
    std::cout << "\nEsperado:                      " << esperado << "\n\n";
}

int main() {
    // Casos propios: el enunciado no proporciona ejemplos para la p15.
    // En cada caso no vacio, ambas pilas tienen la misma cantidad de hojas.
    probar("1. Paginas alternadas",
           {5, 3, 1}, {2, 4, 6}, "1 2 3 4 5 6");

    probar("2. INICIO contiene las paginas menores",
           {3, 2, 1}, {4, 5, 6}, "1 2 3 4 5 6");

    probar("3. FIN contiene las paginas menores",
           {6, 5, 4}, {1, 2, 3}, "1 2 3 4 5 6");

    probar("4. Mezcla de ocho paginas",
           {8, 7, 3, 2}, {1, 4, 5, 6}, "1 2 3 4 5 6 7 8");

    probar("5. Una hoja por pila, menor en INICIO",
           {1}, {2}, "1 2");

    probar("6. Una hoja por pila, menor en FIN",
           {2}, {1}, "1 2");

    // Caso limite adicional: libro sin hojas.
    probar("7. Ambas pilas vacias",
           {}, {}, "[vacia]");

    return 0;
}

