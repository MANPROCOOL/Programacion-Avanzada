#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    long long cantidad, min_valor = 1000000001;
    int dia_lanzamiento = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &cantidad);
        if (cantidad < min_valor) {
            min_valor = cantidad;
            dia_lanzamiento = i;
        }
    }
    printf("%d\n", dia_lanzamiento);

    return 0;
}