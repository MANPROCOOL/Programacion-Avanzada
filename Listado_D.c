#include <stdio.h>
#include <math.h>

int main() {
    int lado, angulo;
    scanf("%d%d",&lado, &angulo);
    float resultado;
    resultado = (lado * sin(angulo * 3.1415 / 180));
    resultado = round(resultado);
    printf("%.3f", resultado);
    return 0;
}