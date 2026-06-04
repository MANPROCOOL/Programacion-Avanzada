#include "../promedio.h"
#include <float.h>

float promedio(float* numeros, int cantidad){
    if (cantidad <= 2) return 0.0; // Evitar división por cero o negativos

    float total = 0;
    float min = FLT_MAX;
    float max = -FLT_MAX; // Corrección: FLT_MIN es el positivo más cercano a 0, no el más negativo

    for (int i = 0; i < cantidad; i++){
        total += numeros[i];
        if (min > numeros[i])  min = numeros[i];
        if (max < numeros[i])  max = numeros[i];
    }
    
    // Restamos los extremos y dividimos por el nuevo total de elementos
    return (total - min - max) / (float)(cantidad - 2);
}