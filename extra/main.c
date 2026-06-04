#include <stdio.h>
#include "promedio.h"


int main(){
    const int cantidad = 5;
    float numeros[5] = {1.2, 3.2, 4.0, 5.2, 6.0};

    printf("Promedio: %f\n", promedio(numeros, cantidad));
}
