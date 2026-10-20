#include "tCola.h"
#include "tPila.h"

// ── El Faro Shuffle ───────────────────────────────
//
void intercalar(tCola& q) { 
    tPila auxiliar; // la unica pila auxiliar que puedo usar
    int tam = q.size();
    for (int i = 0; i < q.size()/2 ; i++){ // Dejare B en frente
        q.enqueue(q.frontValue());
        q.dequeue();
    }
    while (auxiliar.size() != tam/2){ // Metere B en aux
        auxiliar.push(q.frontValue());
        q.dequeue();
    }
    while (auxiliar.size()){ // Metere aux de vuelta en q, quedara invertida
        q.enqueue(auxiliar.topValue());
        auxiliar.pop();
    }
    // despues de esto en q tengo A1 A2 A3 B3 B2 B1
    for (int i = 0; i < q.size()/2 ; i++){ // Dejare B en frente
        q.enqueue(q.frontValue());
        q.dequeue();
    }
    while (auxiliar.size() != tam/2){  // Metere B en aux
        auxiliar.push(q.frontValue()); // B esta invertida
        q.dequeue();
    }
    // Ahora tengo en q A1 A2 A3 y en aux B3 B2 B1, todo listo para encolar
    while (auxiliar.size()){
        q.enqueue(q.frontValue());
        q.dequeue();
        q.enqueue(auxiliar.topValue());
        auxiliar.pop();
    }
}
