#include <stdio.h>

int main() {
    int corx, cordy, resultado;
    scanf("%d %d", &corx, &cordy);
    if (corx > 0 && cordy > 0) {
        resultado = 1;
    } else if (corx < 0 && cordy > 0) {
        resultado = 2;
    } else if (corx < 0 && cordy < 0) {
        resultado = 3;
    } else if (corx > 0 && cordy < 0) {
        resultado = 4;
    } else {
        resultado = 0;
    }
    printf("%d", resultado);
    return 0;
}