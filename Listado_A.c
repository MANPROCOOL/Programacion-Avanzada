#include <stdio.h>
#include <math.h>

int main() {
    int numero;
    scanf("%d", &numero);
    long long operador1, operador2, resultado;
    operador1 = pow(2, numero);
    operador2 = operador1 + 1;
    resultado = pow(operador2,2);
    printf("%lld", resultado);
    return 0;
}