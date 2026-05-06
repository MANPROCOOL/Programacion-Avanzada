#include <stdio.h>

void imprimir_matriz(int filas, int columnas, char matriz[101][82]) {
    for (int i = filas - 1; i >= 0; i--) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ordenar(int filas, int columnas, char matriz[101][82]) {
    int cant[82], min = 0;

    // Calcular altura de cada columna
    for (int j = 0; j < columnas; j++) {
        cant[j] = 0;
        for (int i = 0; i < filas; i++) {
            if (matriz[filas - 1 - i][j] == '*') {
                cant[j] = i;
            }
        }
    }

    // Reordenar columnas
    for (int i = 0; i < columnas; i++) {
        int encontrado = 0;
        for (int k = 0; k < columnas && !encontrado; k++) {
            if (cant[k] == min) {
                encontrado = 1;

                for (int m = 0; m < filas; m++) {
                    if (m == cant[k]) matriz[m][i] = '*';
                    else matriz[m][i] = '.';
                }

                cant[k] = -1; // marcar como usada
            }
        }

        if (!encontrado) {
            min++;
            i--; // reintentar con el mismo i
        }
    }
}

int main() {
    char lineas[101][82]; 
    int i = 0, columnas = 0, i_ = 0;
    char c;

    while (scanf("%c", &c) != EOF) {
        if (c == '\r') continue;  // ignorar CR (Windows)

        lineas[i][i_] = c;
        i_++;

        if (c == '\n') {
            lineas[i][i_] = '\0';

            if (i_ > 1) {  // línea con contenido
                columnas = i_ - 1;
                i++;
                i_ = 0;
            } else {  // línea en blanco => procesar bloque
                if (i > 0) {
                    ordenar(i, columnas, lineas);
                    imprimir_matriz(i, columnas, lineas);
                }
                i = 0;
                i_ = 0;
            }
        }
    }

    // Procesar último bloque si no termina en línea en blanco
    if (i > 0) {
        ordenar(i, columnas, lineas);
        imprimir_matriz(i, columnas, lineas);
    }

    return 0;
}