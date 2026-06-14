#include <stdio.h>
#include <stdlib.h> // Para usar abs()

// En C, pasamos 'dim' primero y luego la matriz usando esa misma variable
int seguro(int dim, int tablero[dim][dim], int fila, int col) {
    int i, j;
    for (i = fila - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j] == 1) return 0;}
    for (i = fila - 1, j = col + 1; i >= 0 && j < dim; i--, j++) {
        if (tablero[i][j] == 1) return 0;}
    for (i = fila + 1, j = col - 1; i < dim && j >= 0; i++, j--) {
        if (tablero[i][j] == 1) return 0;}
    for (i = fila + 1, j = col + 1; i < dim && j < dim; i++, j++) {
        if (tablero[i][j] == 1) return 0;}
    return 1; // Si sobrevivió a los 4 caminos, la casilla está totalmente aislada y segura
}

// Función recursiva casilla por casilla
int maxAlfilesRecursivo(int dim, int tablero[dim][dim], int fila, int col, int alfilesColocados) {
    // Si nos pasamos de la última columna, saltamos a la siguiente fila
    if (col == dim) {
        fila++;
        col = 0;
    }
    // CASO BASE: Si ya recorrimos todo el tablero

    int maxGlobal = 0;
    // OPCIÓN 1: Intentar colocar un alfil en la casilla actual (fila, col)
    if (seguro(dim, tablero, fila, col)) {
        tablero[fila][col] = 1; // Colocamos el alfil
        int conAlfil = maxAlfilesRecursivo(dim, tablero, fila, col + 1, alfilesColocados + 1);
        if (conAlfil > maxGlobal) {
            maxGlobal = conAlfil;
        }  
        tablero[fila][col] = 0; // Backtrack (quitamos el alfil)
    }
    // OPCIÓN 2: Probar el camino dejando la casilla actual VACÍA
    int sinAlfil = maxAlfilesRecursivo(dim, tablero, fila, col + 1, alfilesColocados);
    if (sinAlfil > maxGlobal) {
        maxGlobal = sinAlfil;
    }

    return maxGlobal;
}

int main() {
    int dim;
    scanf("%d", &dim);
    int tablero[dim][dim];
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tablero[i][j] = 0;
        }
    }
    int maximo = maxAlfilesRecursivo(dim, tablero, 0, 0, 0); // Arrancamos la recursividad
    printf("El numero maximo de alfiles para dim=%d es: %d\n", dim, maximo);
    return 0;
}