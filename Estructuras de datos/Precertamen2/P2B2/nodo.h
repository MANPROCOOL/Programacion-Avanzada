#ifndef NODO_H
#define NODO_H
#include <string>

typedef int tipoElem;

struct tNodoArbolBin {
    tipoElem info;
	std::string accion;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

#endif
