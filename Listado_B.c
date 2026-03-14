#include <stdio.h>

int main() {
    int articulos, impacto;
    float resultado;
    scanf("%d%d",&articulos, &impacto);
    resultado = (articulos * (impacto - 1)) + 1;
    printf("%.0f", resultado);
    return 0;
}