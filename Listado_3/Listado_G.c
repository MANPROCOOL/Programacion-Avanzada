#include <stdio.h>

int longitud_cadena(char cadena[101]) {
    int i = 0;
    while (cadena[i] != '\0') {
        i++;
    }
    return i;
}

int max_divisor(int longitud) {
    int max = 1;
    for (int i = 2; i < longitud; i++) {
        if (longitud % i == 0 && i <= longitud / i) {
            max = i;
        }
    }
    return max;
}

int main () {
    char cadena[101], final[101];
    scanf("%s", cadena);
    int longitud = longitud_cadena(cadena), index = 0;
    int max = max_divisor(longitud);
    char matriz[max][longitud / max];
    for (int i = 0; i < longitud / max; i++){
        for (int j = 0; j < max; j++) {
            matriz[j][i] = cadena[index++];
        }
    }
    int new_index = 0;
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < longitud / max; j++) {
            final[new_index++] = matriz[i][j];
        }
    }
    final[new_index] = '\0';
    printf("%s\n", final);
    return 0;
}