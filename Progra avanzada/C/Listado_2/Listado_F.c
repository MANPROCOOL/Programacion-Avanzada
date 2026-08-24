#include <stdio.h>

int main() {
    int conteo[13] = {0}, max_fuerza = 0;
    char carta[3];

    for (int i = 0; i < 5; i++) {
        scanf("%s", carta);
        char rango = carta[0];
        int indice;
        if (rango == 'A') indice = 0;
        else if (rango == 'T') indice = 9;
        else if (rango == 'J') indice = 10;
        else if (rango == 'Q') indice = 11;
        else if (rango == 'K') indice = 12;
        else {
            indice = (rango - '0') - 1; 
        }
        conteo[indice]++;
    }
    for (int i = 0; i < 13; i++) {
        if (conteo[i] > max_fuerza) {
            max_fuerza = conteo[i];
        }
    }
    printf("%d", max_fuerza);
    return 0;
}