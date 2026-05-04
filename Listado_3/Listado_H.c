#include <stdio.h>
#include <string.h>

int lengstr(char comprobar[82]) {
    int i = 0;
    while (comprobar[i] != '\n' && comprobar[i] != '\0') {
        i++;
    }
    return i;
}

void llenar_matriz(int filas, int columnas, char matriz[filas][columnas], char cadena[8200]) {
    int index = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = cadena[index++];
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
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == '*') {
                matriz[i][j] = '.';
                matriz[i][limite] = '*';
                limite--;
            }
        }
    }
}


int main() {
    char linea[82] = "", cadena[8202] = "";
    int bandera = 1, contador = 0, filas = 0, columnas = 0;
    while (bandera) {
        fgets(linea, 82, stdin);
        filas++;
        if (linea[0] == '\n' && contador == 0) {
            contador++;
            char matriz[filas][columnas];
            llenar_matriz(filas, columnas, matriz, cadena);
            mover_a_la_derecha(filas, columnas, matriz);
            imprimir_matriz(filas, columnas, matriz);
            printf("\n");
            char cadena[8202] = ""; // Reinicio la cadena para la siguiente matriz
            filas = 0; // Reinicio el contador de filas para la siguiente matriz

        }
        if (linea[0] != '\n') {
            contador = 0;
            linea[strcspn(linea, "\n")] = '\0';
            strcat(cadena, linea);
            filas++;
            columnas = lengstr(linea);

        }
        if (contador == 2) {
            bandera = 0;
        }    
    }
    return 0;
}

