#include <stdio.h>

int main() {
    int minutos, intentos_fallidos[26] = {0}, problemas_resueltos = 0, tiempo_total = 0;
    char problema_char, resultado[10];

    while (scanf("%d", &minutos) == 1 && minutos != -1) {
        scanf(" %c %s", &problema_char, resultado);
        int idx = problema_char - 'A';
        if (resultado[0] == 'r') {
            problemas_resueltos++;
            tiempo_total += minutos + (intentos_fallidos[idx] * 20);   
        } else {
            intentos_fallidos[idx]++;
        }
    }
    printf("%d %d\n", problemas_resueltos, tiempo_total);
    return 0;
}