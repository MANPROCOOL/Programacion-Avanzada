#include <iostream>
#include <initializer_list>
#include "ABB.hpp"
#include "Cola.hpp"

/*
Pregunta 23: verificar si Q contiene EXACTAMENTE el postorden de A.
El enunciado no fija nombre ni firma: usamos verificarPostorden.

- raiz representa un arbol binario GENERAL de enteros, no necesariamente ABB.
- Q es tu tCola original de enteros.
- Debes retornar true si toda la secuencia coincide y false en otro caso.
- Tiempo requerido: O(n), donde n es la cantidad de nodos del arbol.
- No modificar ni liberar los nodos del arbol.

Convenciones del esqueleto:
- Se permite consumir Q: el enunciado no exige conservarla.
- Un arbol vacio tiene un recorrido vacio.
- Cada prueba construye su propia cola.
- Puedes agregar una funcion auxiliar si lo necesitas.
- ABB.hpp se incluye solo para reutilizar tu struct tNodo:
  info, izq y der. No se instancia un tABB.

Operaciones de tu cola:
  Q.enqueue(entero); Q.frontValue(); Q.dequeue(); Q.size(); Q.clear();
Consultar o eliminar requiere Q.size() > 0.
dequeue elimina sin retornar un valor.
*/

void postorden(tNodo* nodo, tCola& resultado){

	if (nodo == nullptr){return;}
	postorden(nodo->izq, resultado);
	postorden(nodo->der, resultado);
	resultado.enqueue(nodo->info);

}

bool verificarPostorden(tNodo* raiz, tCola& Q) {

	tCola comprobar;
	postorden(raiz, comprobar); // ya tengo el recorrido post-orden en la cola
	//ahora necesito compararlos
	while(Q.size() && comprobar.size()){
		if (Q.frontValue() != comprobar.frontValue()){return false;}
		Q.dequeue(), comprobar.dequeue();
	}
	if (Q.size() || comprobar.size()){
		return false;
	}
	return true;

}

// Infraestructura de pruebas: no necesitas modificarla.
// Los elementos se escriben en orden FRENTE -> FINAL.
void probar(const char* nombre, tNodo* raiz, std::initializer_list<int> secuencia, bool esperado) {
    tCola Q;
    for (int valor : secuencia) Q.enqueue(valor);

    std::cout << nombre << "\nCola (frente -> final): ";
    if (secuencia.size() == 0) std::cout << "[vacia]";
    for (int valor : secuencia) std::cout << valor << ' ';

    bool obtenido = verificarPostorden(raiz, Q);
    std::cout << "\nTu output: " << std::boolalpha << obtenido << "\nEsperado:  " << esperado << "\n\n";
}

int main() {
    std::cout << "Funcion pendiente: el esqueleto retorna false provisionalmente.\n\n";

    // El ejercicio no proporciona ejemplos. Todos estos casos son propios.
    // Arbol de prueba:
    // 15: hijos 9 y 20.
    // 9: hijos 7 y 12.
    // 20: hijos 19 y 25.
    // 19: hijo izquierdo 18. 25: hijo izquierdo 21.
    tNodo n7{7, nullptr, nullptr}, n12{12, nullptr, nullptr};
    tNodo n18{18, nullptr, nullptr}, n21{21, nullptr, nullptr};
    tNodo n19{19, &n18, nullptr}, n25{25, &n21, nullptr};
    tNodo n9{9, &n7, &n12}, n20{20, &n19, &n25};
    tNodo n15{15, &n9, &n20};

    probar("1. Postorden correcto", &n15,
           {7, 12, 9, 18, 19, 21, 25, 20, 15}, true);

    probar("2. Misma cantidad, orden incorrecto", &n15,
           {12, 7, 9, 18, 19, 21, 25, 20, 15}, false);

    probar("3. Cola mas corta: falta la raiz", &n15,
           {7, 12, 9, 18, 19, 21, 25, 20}, false);

    probar("4. Recorrido correcto con un elemento sobrante", &n15,
           {7, 12, 9, 18, 19, 21, 25, 20, 15, 99}, false);

    probar("5. Arbol no vacio y cola vacia", &n15, {}, false);

    probar("6. Arbol y cola vacios", nullptr, {}, true);
    probar("7. Arbol vacio y cola no vacia", nullptr, {5}, false);

    tNodo unico{42, nullptr, nullptr};
    probar("8. Solo raiz, coincide", &unico, {42}, true);
    probar("9. Solo raiz, valor incorrecto", &unico, {41}, false);

    // Arbol general que NO es ABB.
    tNodo g99{99, nullptr, nullptr};
    tNodo g30{30, nullptr, &g99}, gMenos5{-5, nullptr, nullptr};
    tNodo g10{10, &g30, &gMenos5};
    probar("10. Arbol general: postorden correcto", &g10,
           {99, 30, -5, 10}, true);

    // Las repeticiones se comparan como parte de la secuencia.
    tNodo rIzq{5, nullptr, nullptr}, rDer{5, nullptr, nullptr};
    tNodo rRaiz{5, &rIzq, &rDer};
    probar("11. Valores repetidos, cantidad correcta", &rRaiz,
           {5, 5, 5}, true);
    probar("12. Valores repetidos, falta un elemento", &rRaiz,
           {5, 5}, false);
    return 0;
}