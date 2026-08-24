#include <iostream>
#include <math.h>

using namespace std;

// Función de Backtracking que hace la búsqueda inteligente
int buscarCombinaciones(int destino, int potencia, int numero_actual, int suma_actual) {
    // 1. SI LLEGAMOS AL OBJETIVO: Encontramos una combinación válida, sumamos 1
    if (suma_actual == destino) {
        return 1;
    }
    
    // 2. ¡TU REGLA DE FRENO!: Si la suma actual ya superó el destino,
    // nos detenemos inmediatamente (return 0) y esa rama no sigue gastando tiempo.
    if (suma_actual > destino) {
        return 0;
    }
    
    // Calculamos la potencia del número en el que vamos (ej: 1^2, 2^2, 3^2...)
    int valor_potencia = pow(numero_actual, potencia);
    
    // 3. OTRA OPTIMIZACIÓN: Si el número solo ya se pasa del destino (ej: 11^2 = 121 y el destino es 100),
    // significa que no hay más números naturales hacia adelante que puedan servir.
    if (valor_potencia > destino) {
        return 0;
    }

    // El Backtracking abre dos caminos en cada paso (como un árbol de decisión):
    
    // Camino A: Decidimos "encender" (sumar) el número actual y pasar al siguiente número
    int tomar = buscarCombinaciones(destino, potencia, numero_actual + 1, suma_actual + valor_potencia);
    
    // Camino B: Decidimos "apagar" (saltarnos) el número actual y pasar al siguiente directamente
    int no_tomar = buscarCombinaciones(destino, potencia, numero_actual + 1, suma_actual);
    
    // Retornamos la suma de todos los caminos válidos que encontramos
    return tomar + no_tomar;
}

int main() {
    int destino;
    int potencia;
    cin >> destino;
    cin >> potencia;
    cout << buscarCombinaciones(destino, potencia, 1, 0);
    return 0;
}