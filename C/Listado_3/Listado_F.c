#include <stdio.h>
int contar_pasos(int filas, int columnas, char matriz[filas][columnas]) {
    int pasos = 1, bandera = 1;
     for (int i = 0; i < columnas; i++) {
        bandera = 1;
        for (int j = 0; j < filas; j++) {
            if (matriz[j][i] != '_') {
                bandera = 0;
            }
        }
        if (bandera) {
            pasos++;
        }
     }
    return pasos;
}

int main() {
    int filas, columnas;
    scanf("%d %d", &filas, &columnas);
    char matriz[filas][columnas];
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }
    printf("%d\n", contar_pasos(filas, columnas, matriz));
}