#include <stdio.h>
#include <string.h>

int lengstr(char comprobar[82]) {
    int i = 0;
    while (comprobar[i] != '\n' && comprobar[i] != '\r' && comprobar[i] != '\0') {
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

void ordenar_columnas(int filas, int columnas, char matriz[filas][columnas]) {
    int pos_asterisco[82];
    
    // 1. Encontrar en qué fila está el asterisco para cada columna
    for (int j = 0; j < columnas; j++) {
        for (int i = 0; i < filas; i++) {
            if (matriz[i][j] == '*') {
                pos_asterisco[j] = i;
            }
        }
    }

    // 2. Método de burbuja para ordenar las columnas según esa posición
    for (int j = 0; j < columnas - 1; j++) {
        for (int k = 0; k < columnas - j - 1; k++) {
            // Si la posición es menor (está más arriba), la movemos a la derecha
            if (pos_asterisco[k] < pos_asterisco[k+1]) {
                
                // Intercambiar las posiciones registradas
                int temp_pos = pos_asterisco[k];
                pos_asterisco[k] = pos_asterisco[k+1];
                pos_asterisco[k+1] = temp_pos;

                // Intercambiar TODA la columna dentro de tu matriz
                for (int i = 0; i < filas; i++) {
                    char temp_char = matriz[i][k];
                    matriz[i][k] = matriz[i][k+1];
                    matriz[i][k+1] = temp_char;
                }
            }
        }
    }
}

int main() {
    int i = 0, columnas;
    char matriz[100][82];
    int primera_vez = 1;

    while (fgets(matriz[i], 82, stdin) != NULL) {
        
        if (matriz[i][0] == '\n' || matriz[i][0] == '\r') {
            if (i > 0) {
                columnas = lengstr(matriz[0]);
                char procesar[i][columnas];
                llenar_matriz(i, columnas, procesar, matriz);
                ordenar_columnas(i, columnas, procesar);         
                if (!primera_vez) printf("\n");
                imprimir_matriz(i, columnas, procesar);  
                primera_vez = 0;
                i = 0; // Reiniciamos el contador de filas para el siguiente log
            }
        } 
        else {
            i++; // Solo aumentamos "i" si la línea no era el separador
        }
    }
    
    // Al salir del bucle, procesamos el último log (si el archivo no termina en línea blanca)
    if (i > 0) { // Osea se cumpe el NULL
        columnas = lengstr(matriz[0]);
        char procesar[i][columnas];
        llenar_matriz(i, columnas, procesar, matriz);
        ordenar_columnas(i, columnas, procesar);
        if (!primera_vez) printf("\n");
        imprimir_matriz(i, columnas, procesar);
    }
    return 0;
}