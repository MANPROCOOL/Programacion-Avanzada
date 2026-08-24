#include <stdio.h>
#include <math.h>

int main() {
    long current, hasta, temp, digito;
    long suma;
    int n_digitos;

    if (scanf("%ld %ld", &current, &hasta) != 2) return 1;

    while (current <= hasta) {
        if (current == 0) {
            n_digitos = 1;
        } else {
            n_digitos = floor(log10(labs(current))) + 1;
        }

        suma = 0;
        temp = current;

        while (temp > 0) {
            digito = temp % 10;
            suma += pow(digito, n_digitos);
            temp /= 10;
        }
        if (suma == current) {
            printf("%ld ", current);
        }

        current++;
    }

    printf("\n");
    return 0;
}