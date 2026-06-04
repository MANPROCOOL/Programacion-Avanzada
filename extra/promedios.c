#include "promedio.h"
#include <float.h>

float aritmetico(float* numeros, int cantidad){
    int total = 0;
    for (int i=0; i < cantidad; i++){
        total += numeros[i];
    }
    return total / (float)cantidad;
}

float sin_extremos(float* numeros, int cantidad){
    float total = 0;
    float min = FLT_MAX;
    float max = FLT_MIN;

    for (int i=0; i < cantidad; i++){
        total += numeros[i];
        if (min > numeros[i])
            min = numeros[i];
        if (max < numeros[i])
            max = numeros[i];
    }
    return (total - max - min) / ((float)cantidad - 2);
}