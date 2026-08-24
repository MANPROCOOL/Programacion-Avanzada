#include <stdio.h>

int es_mayor(int filas, int columnas, char matriz[filas][columnas], int col_a) {
    for (int i = 0; i < filas; i++) {
        char a = matriz[i][col_a];
        char b = matriz[i][col_a + 1];
        
        char a_min = a;
        char b_min = b;

        if (a >= 'A' && a <= 'Z') a_min = a + 32;
        if (b >= 'A' && b <= 'Z') b_min = b + 32;

        if (a_min > b_min) return 1;
        if (a_min < b_min) return 0;
    }
    return 0;
}

void imprimir_matriz(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

int main () {
    int filas = 1, columnas = 1;
    while (filas != 0 && columnas != 0) {
        scanf("%d %d", &filas, &columnas);
        char matriz[filas][columnas];
        char cadena[16];
        for (int i = 0; i < filas; i++) {
            scanf("%s", cadena);
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = cadena[j];
            }
        }
        for (int i = 0; i < columnas - 1; i++) {
            for (int j = 0; j < columnas - 1 - i; j++) {
                if (es_mayor(filas, columnas, matriz, j)) {
                    for (int k = 0; k < filas; k++) {
                        char temp = matriz[k][j];
                        matriz[k][j] = matriz[k][j+1];
                        matriz[k][j+1] = temp;
                    }
                }
            }
        }
        imprimir_matriz(filas, columnas, matriz);
        printf("\n");
    }
    return 0;
}