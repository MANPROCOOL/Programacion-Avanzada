#include "../promedio.h"

float promedio(float* numeros, int cantidad){
    float total = 0; // Corrección: float para no perder decimales
    for (int i = 0; i < cantidad; i++){
        total += numeros[i];
    }
    return total / (float)cantidad;
}