#include <stdio.h>
#include <string.h>

int lengstr(char comprobar[82]) {
    int i = 0;
    while (comprobar[i] != '\n' && comprobar[i] != '\0') {
        i++;
    }
    return i;
}

void llenar_matriz(int filas, int columnas, char matriz[filas][columnas], char start[100][82]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = start[i][j];
        }
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

void mover_a_la_derecha(int filas, int columnas, char matriz[filas][columnas]) {
    int limite = columnas - 1;
    for (int i = 0; i < filas; i++) {
        for (int j = columnas - 1; j >= 0 && limite >= 0; j--) {
            if (matriz[i][limite] == '*') {limite--;}
            if (matriz[i][j] == '*' && matriz[i][limite] != '*' ) {
                matriz[i][j] = '.';
                matriz[i][limite] = '*';
                limite--;
            }
        }
    }
}

void mover_a_la_izquierda(int filas, int columnas, char matriz[filas][columnas]){
    for (int i = 0; i < filas; i++) {
        int limite = 0;
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == '*') {
                matriz[i][j] = '.';
                matriz[i][limite] = '*';
                limite++;
            }
        }
    }
}



int main() {
    int i = 0, columnas;
    char matriz[100][82];
    while (fgets(matriz[i++], 82, stdin) != NULL) {
        if (matriz[i-1][0] == '\n') {
            i--;
            columnas = lengstr(matriz[0]);
            char procesar[i][columnas];
            llenar_matriz(i, columnas, procesar, matriz);
            mover_a_la_izquierda(i, columnas, procesar);
            mover_a_la_derecha(i, columnas, procesar);
            imprimir_matriz(i, columnas, procesar);
            i = 0;
        }
    }
}

