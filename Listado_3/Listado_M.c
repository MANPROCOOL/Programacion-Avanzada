#include <stdio.h>

void limpiar_cadena(int cantidad, int cadena[cantidad]) {
    for (int i = 0; i < cantidad; i++) {
        cadena[i] = 0;
    }
}

int main () {

    int cantidad = 0, total = 1;
    scanf("%d", &cantidad);
    int cadena[cantidad], final[cantidad];
    limpiar_cadena(cantidad, cadena);
    limpiar_cadena(cantidad, final);
    for (int i = 0; i < cantidad; i++) {
        scanf(" %d", &cadena[i]);
    }
    final[0] = cadena[0];
    for (int i = 0, j = 0; i < cantidad - 1; i++) {
        if (cadena[i+1] > final[j]) {
            final[j+1] = cadena[i+1];
            j++;
            total++;
        }
    }
    printf("%d\n", total);
    for (int i = 0; i < total; i++) {
        printf("%d ", final[i]);
    }

    return 0;
}