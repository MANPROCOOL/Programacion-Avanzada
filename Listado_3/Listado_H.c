#include <stdio.h>
#include <string.h>

int lengstr(char comprobar[82]) {
    int i = 0;
    while (comprobar[i] != '\n' && comprobar[i] != '\0') {
        i++;
    }
    return i;
}

void imprimir_matriz(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

// Devuelve la fila donde está el '*' en la columna col
int valor_columna(int filas, int columnas, char matriz[filas][columnas], int col) {
    for (int i = 0; i < filas; i++) {
        if (matriz[i][col] == '*') return i;
    }
    return -1;
}

// Intercambia dos columnas
void swap_columnas(int filas, int columnas, char matriz[filas][columnas], int a, int b) {
    for (int i = 0; i < filas; i++) {
        char temp = matriz[i][a];
        matriz[i][a] = matriz[i][b];
        matriz[i][b] = temp;
    }
}

void ordenar_columnas(int filas, int columnas, char matriz[filas][columnas]) {
    for (int i = 0; i < columnas - 1; i++) {
        for (int j = 0; j < columnas - 1 - i; j++) {
            // asterisco más abajo = valor más alto = va a la derecha
            if (valor_columna(filas, columnas, matriz, j) < valor_columna(filas, columnas, matriz, j + 1)) {
                swap_columnas(filas, columnas, matriz, j, j + 1);
            }
        }
    }
}

int main() {
    int i = 0, columnas;
    char lineas[100][82];
    int primer_log = 1;

    while (fgets(lineas[i], 82, stdin) != NULL) {
        if (lineas[i][0] == '\n') {
            if (i > 0) {
                columnas = lengstr(lineas[0]);
                char procesar[i][columnas];
                for (int r = 0; r < i; r++)
                    for (int c = 0; c < columnas; c++)
                        procesar[r][c] = lineas[r][c];

                if (!primer_log) printf("\n");
                primer_log = 0;

                ordenar_columnas(i, columnas, procesar);
                imprimir_matriz(i, columnas, procesar);
                i = 0;
            }
        } else {
            i++;
        }
    }

    // Procesar el último log (sin blank line al final)
    if (i > 0) {
        columnas = lengstr(lineas[0]);
        char procesar[i][columnas];
        for (int r = 0; r < i; r++)
            for (int c = 0; c < columnas; c++)
                procesar[r][c] = lineas[r][c];

        if (!primer_log) printf("\n");
        ordenar_columnas(i, columnas, procesar);
        imprimir_matriz(i, columnas, procesar);
    }

    return 0;
}