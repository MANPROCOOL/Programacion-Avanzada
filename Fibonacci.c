#include <stdio.h>

int fibonacci(int n) {

    if (n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        // Llamada recursiva: F(n) = F(n-1) + F(n-2)
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n = 0; // Ejemplo: calcular el décimo término
    scanf("%d", &n);
    printf("El termino %d de la serie de Fibonacci es: %d\n", n, fibonacci(n));
    return 0;
}