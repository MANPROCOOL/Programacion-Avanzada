#include <stdio.h>

void limpiar_matriz(int filas, char matriz[filas][26]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 26; j++) {
            matriz[i][j] = '\0';
        }
    }
}

void imprimir_matriz(int filas, char matriz[filas][26]) {
    for (int i = 0; i < filas; i++) {
        printf("%s\n", matriz[i]);
    }
}

int main() {
    
    int filas = 1, contador = 0;
    while (filas != 0) {
        scanf("%d", &filas);
        contador++;
        char matriz[filas][26], final[filas][26];
        limpiar_matriz(filas, matriz);
        limpiar_matriz(filas, final);
        for (int i = 0; i < filas; i++) {
            scanf("%s", matriz[i]);
        }
        if (filas % 2 == 0) {
            for (int j = 0, w = 0; j < filas ; j+=2, w++) {
                for (int k = 0; k < 26; k++) {
                    final[w][k] = matriz[j][k];
                    final[filas - 1 - w][k] = matriz[j+1][k];
                }
            }
        }
        else {
            for (int j = 0, w = 0; j < filas ; j+=2, w++) {
                for (int k = 0; k < 26; k++) {
                    final[w][k] = matriz[j][k];
                    final[filas - 1 - w][k] = matriz[j+1][k];
                }
            }
            for (int k = 0; k < 26; k++) {
                final[filas / 2][k] = matriz[filas - 1][k];
            }
        }
        if (filas != 0) {
            printf("SET %d\n", contador);
            imprimir_matriz(filas, final);
        }
    }
    return 0;
}