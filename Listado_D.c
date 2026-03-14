#include <stdio.h>
#include <math.h>

int main() {
    int lado, angulo;
    scanf("%d%d",&lado, &angulo);
    float resultado;
    resultado = (lado / sin(angulo * 3.14159265359 / 180));
    resultado = ceil(resultado);
    printf("%.0f", resultado);
    return 0;
}