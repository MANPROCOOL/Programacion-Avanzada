#include <stdio.h>

// Compara dos columnas lexicograficamente ignorando case, retorna 1 si col_a > col_b
int columna_mayor(int filas, int columnas, char matriz[filas][columnas], int col_a, int col_b) {
    for (int i = 0; i < filas; i++) {
        char a = matriz[i][col_a];
        char b = matriz[i][col_b];

        // Convertir a minuscula para comparar
        if (a >= 'A' && a <= 'Z') a = a + 32;
        if (b >= 'A' && b <= 'Z') b = b + 32;

        if (a > b) return 1;
        if (a < b) return 0;
    }
    return 0; // Son iguales
}

void imprimir_bloque(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int filas, columnas;
    int primer_bloque = 1;

    while (scanf("%d %d", &filas, &columnas) == 2 && (filas != 0 || columnas != 0)) {
        char matriz[filas][columnas];
        char fila_buf[16];

        for (int i = 0; i < filas; i++) {
            scanf("%s", fila_buf);
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = fila_buf[j];
            }
        }

        // Insertion sort estable sobre columnas (estable por definicion)
        for (int i = 1; i < columnas; i++) {
            int j = i;
            while (j > 0 && columna_mayor(filas, columnas, matriz, j - 1, j)) {
                // Swap de columnas j-1 y j
                for (int k = 0; k < filas; k++) {
                    char temp = matriz[k][j - 1];
                    matriz[k][j - 1] = matriz[k][j];
                    matriz[k][j] = temp;
                }
                j--;
            }
        }

        if (!primer_bloque) printf("\n"); // Linea en blanco entre bloques
        imprimir_bloque(filas, columnas, matriz);
        primer_bloque = 0;
    }

    return 0;
}