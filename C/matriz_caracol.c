#include <stdio.h>

int main () { //llenar una matriz de forma caracol
    int fila, columna, f = 0;
    scanf("%d %d", &fila, &columna);
    int matriz[fila][columna];
    int superior = 0, inferior = fila - 1, izquierda = 0, derecha = columna - 1;
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int j = 0; j < fila * columna; j++) {
        for (int i = izquierda; i <= derecha; i++) {
            matriz[superior][i] = f++;
        }
        superior++;

        for (int i = superior; i <= inferior; i++) {
            matriz[i][derecha] = f++;
        }
        derecha--;

        for (int i = derecha; i >= izquierda; i--) {
            matriz[inferior][i] = f++;
        }
        inferior--;

        for (int i = inferior; i >= superior; i--) {
            matriz[i][izquierda] = f++;
        }
        izquierda++;
    }

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}