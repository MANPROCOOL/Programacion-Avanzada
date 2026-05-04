#include <stdio.h>

void limpiar_matriz(int filas, char matriz[filas][21]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 21; j++) {
            matriz[i][j] = '\0';
        }
    }
}

void imprimir_matriz(int filas, char matriz[filas][21]) {
    for (int i = 0; i < filas; i++) {
        printf("%s\n", matriz[i]);
    }
}

void limpiar_cadena(char cadena[21]) {
    for (int i = 0; i < 21; i++) {
        cadena[i] = '\0';
    }
}

void organizar(int filas, char matriz[filas][21]) {
    for (int i = 0; i < filas - 1; i++) {
        if (matriz[i][0] > matriz[i+1][0]) {
            char temp[21] = "";
            for (int j = 0; j < 21; j++) {
                temp[j] = matriz[i][j];
                matriz[i][j] = matriz[i+1][j];
                matriz[i+1][j] = temp[j];
            }
            i = -1;
        }
        else if (matriz[i][1] > matriz[i+1][1] && matriz[i][0] == matriz[i+1][0]) {
            char temp[21] = "";
            for (int j = 0; j < 21; j++) {
                temp[j] = matriz[i][j];
                matriz[i][j] = matriz[i+1][j];
                matriz[i+1][j] = temp[j];
            }
            i = -1;
        }
    }
}

int main () {
    int filas = 1;
    char name[21];
    while (filas != 0) {
        scanf("%d", &filas);
        char matriz[filas][21];
        limpiar_matriz(filas, matriz);
        for (int i = 0; i < filas; i++) {
            limpiar_cadena(name);
            scanf("%s", name);
            for (int j = 0; j < 21; j++) {
                matriz[i][j] = name[j];
            }
        }
        organizar(filas, matriz);
        if (filas != 0) {
            imprimir_matriz(filas, matriz);
            printf("\n");
        }
    }
    return 0;
}