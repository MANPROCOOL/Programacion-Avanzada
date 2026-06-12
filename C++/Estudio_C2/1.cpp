#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Tu función 'donde' adaptada para buscar el menor dígito 
// que sea mayor al dígito del pivote (indice)
int donde_menor_mayor(string cadena, int desde, char pivote) {
    int pos_menor = -1; //para el primer valor que hayemos
    for (int i = desde; i < (int)cadena.size(); i++) {
        if (cadena[i] > pivote) {
            if (pos_menor == -1 || cadena[i] < cadena[pos_menor]) {
                pos_menor = i;
            }
        }
    }
    return pos_menor;
}

// Tu función recursiva que va de derecha a izquierda (indice)
string resolver_recursivo(string test, int indice) {
    // Caso base: si recorrimos todo el string y no se pudo, no hay mayor
    if (indice < 0) {
        return "0";
    }

    // Buscamos si a la derecha de 'indice' hay algún dígito mayor
    int pos_cambio = donde_menor_mayor(test, indice + 1, test[indice]);

    if (pos_cambio != -1) {
        // Si lo encontramos, hacemos el intercambio (la idea de tu 'current')
        char temp = test[indice];
        test[indice] = test[pos_cambio];
        test[pos_cambio] = temp;

        // Para que sea el "más pequeño de los mayores", el resto de la derecha
        // debe quedar ordenado de menor a mayor (reemplaza tu bucle de ordenamiento)
        for (int i = indice + 1; i < (int)test.size(); i++) {
            for (int j = i + 1; j < (int)test.size(); j++) {
                if (test[i] > test[j]) {
                    char t = test[i];
                    test[i] = test[j];
                    test[j] = t;
                }
            }
        }
        return test;
    }

    // Si en esta posición no se pudo, vamos al dígito anterior (tu lógica original)
    return resolver_recursivo(test, indice - 1);
}

int main() {
    string cadena = "";
    if (cin >> cadena) {
        // Empezamos desde el penúltimo elemento hacia atrás
        cout << resolver_recursivo(cadena, cadena.size() - 1) << endl;
    }
    return 0; 
}