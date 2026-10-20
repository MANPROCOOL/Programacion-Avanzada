// ─────────────────────────────────────────────────────────────────────────────
//  CERTAMEN 2 — Pilas y Colas
//  A2 – Entrelazado de Señales: El Faro Shuffle
//  INF-20325 Estructuras de Datos | UTFSM 2026-2
// ─────────────────────────────────────────────────────────────────────────────

#include <iostream>
#include "tCola.h"
#include "tPila.h"

void intercalar(tCola& q);   // implementada en intercalar.cpp

int main() {
    int n;
    std::cin >> n;

    tCola q;
    for (int i = 0; i < 2 * n; i++) {
        int v;
        std::cin >> v;
        q.enqueue(v);
    }

    intercalar(q);

    q.print();

    return 0;
}
