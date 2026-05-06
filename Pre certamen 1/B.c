#include <stdio.h>

void llenar_matriz(int filas, int columnas, char matriz[filas][columnas]){
    for (int i = 0; i < filas; i++) {
            scanf("%s", &matriz[i]);
    }
}

void imprimir_matriz(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void limpiar_matriz(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = '\0';
        }
    }
}

int main() {
    int filas, columnas, horizontal, vertical;
    scanf("%d %d %d %d", &filas, &columnas, &vertical, &horizontal);
    char matriz[filas][columnas];
    limpiar_matriz(filas, columnas, matriz);
    llenar_matriz(filas, columnas, matriz);
    char final[filas][columnas*horizontal], finalisima[filas*vertical][columnas*horizontal];
    limpiar_matriz(filas, columnas*horizontal, final);
    limpiar_matriz(filas*vertical, columnas*horizontal, finalisima);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            for (int k = 0; k < horizontal; k++) {
                final[i][j*horizontal + k] = matriz[i][j];
            }
        }
    }

    for (int i = 0; i < filas; i++){
        for (int k = 0; k < vertical; k++){
            for (int j = 0; j < columnas*horizontal; j++){
                finalisima[i*vertical + k][j] = final[i][j];
            }
        }
    }

    imprimir_matriz(filas*vertical, columnas*horizontal, finalisima);

    return 0;
}

