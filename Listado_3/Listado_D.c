#include <stdio.h>

void busqueda_profunda(int filas, int columnas, char matriz[filas][columnas], int *seguidos, char color, int limite) {
    int max_total = 0;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == color) {
                int der = 1, abajo = 1, arr_der = 1, ab_der = 1; //Busco hacia la derecha, hacia abajo, hacia arriba a la derecha y hacia abajo a la derecha
                for (int d = 1; (j + d < columnas) && matriz[i][j + d] == color && d < limite; d++) der++; //Busco en las 4 direcciones del plano
                for (int a = 1; (i + a < filas) && matriz[i + a][j] == color && a < limite; a++) abajo++; //Me aseguro de no salir de la matriz
                for (int ad = 1; (i - ad >= 0 && j + ad < columnas) && matriz[i - ad][j + ad] == color && ad < limite; ad++) arr_der++;
                for (int abd = 1; (i + abd < filas && j + abd < columnas) && matriz[i + abd][j + abd] == color && abd < limite; abd++) ab_der++;

                if (der > max_total) max_total = der;
                if (abajo > max_total) max_total = abajo;
                if (arr_der > max_total) max_total = arr_der;
                if (ab_der > max_total) max_total = ab_der;
            }
        }
    }
    *seguidos = max_total;
}

int main() {
    int filas, columnas, limite, seguidosR, seguidosB;
    scanf("%d %d %d", &filas, &columnas, &limite);

    char matriz[filas][columnas];
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }

    busqueda_profunda(filas, columnas, matriz, &seguidosR, 'R', limite);
    busqueda_profunda(filas, columnas, matriz, &seguidosB, 'B', limite);

    if (seguidosR > seguidosB && seguidosR == limite) {
        printf("RED WINS\n");
    } else if (seguidosB > seguidosR && seguidosB == limite) {
        printf("BLUE WINS\n");
    } else {
        printf("NONE\n");
    }

    return 0;
}