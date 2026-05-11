#include <stdio.h>
#include <math.h>

int main() {
    double numero, resultado;
    int resultado2;
    scanf("%lf", &numero);
    resultado = (numero * 1000 * 5280 / 4854);
    resultado2 = round(resultado);
    printf("%d", resultado2);
    return 0;
}