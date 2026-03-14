#include <stdio.h>

int main() {
    int uso, stock, resultado;
    scanf("%d%d",& uso, & stock);
    resultado = stock - uso;
    if (resultado == 1) {
        printf("Dr. Chaz will have 1 piece of chicken left over!");
    }
    else if (resultado == -1) {
        printf("Dr. Chaz needs 1 more piece of chicken!");
    }
    else if (resultado > 0) {
        printf("Dr. Chaz will have %d pieces of chicken left over!", resultado);
    }
    else {
        printf("Dr. Chaz needs %d more pieces of chicken!", -resultado);
    }
    return 0;
}