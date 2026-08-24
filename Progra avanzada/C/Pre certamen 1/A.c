#include <stdio.h>
#include <string.h>

void limpiar_matriz(int filas, int col, char matriz[filas][col]){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < col; j++){
            matriz[i][j] = '\0';
        }
    }
}

void limpiar_palabra (int columnas, char palabra[columnas]){
    for (int i = 0; i < columnas; i++) {
        palabra[i] = '\0';
    }
}

void saturar_palabra (int columnas, char palabra[columnas]){
    for (int i = 0; i < columnas; i++) {
        palabra[i] = 'z';
    }
}

int main () {
    int filas, columnas;
    scanf("%d %d", &filas, &columnas);

    char inicial[filas + 1][columnas + 1];
    char palabra[columnas + 1], final[columnas + 1];
    
    limpiar_matriz(filas + 1, columnas + 1, inicial);
    saturar_palabra(columnas + 1, final);
    final[columnas] = '\0'; // Asegurar que el "techo" de comparación sea válido
    limpiar_palabra(columnas + 1, palabra);

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            scanf(" %c", &inicial[i][j]);
        }
    }

    // --- HORIZONTAL ---
    for (int i = 0; i < filas; i++){
        int k = 0;
        // Vamos hasta j <= columnas para forzar el 'else' al final de la línea
        for (int j = 0; j <= columnas; j++){
            if (j < columnas && inicial[i][j] != '#') {
                palabra[k++] = inicial[i][j];
                palabra[k] = '\0'; // ¡CRÍTICO! Mantener la cadena cerrada siempre
            } 
            else {
                if (strlen(palabra) >= 2) {
                    if (strcmp(palabra, final) < 0) {
                        strcpy(final, palabra);
                    }
                }
                k = 0;
                limpiar_palabra(columnas + 1, palabra);
            }
        }
    }

    // --- VERTICAL ---
    for (int j = 0; j < columnas; j++){
        int k = 0;
        // Vamos hasta i <= filas para procesar la última palabra de la columna
        for (int i = 0; i <= filas; i++){
            if (i < filas && inicial[i][j] != '#') {
                palabra[k++] = inicial[i][j];
                palabra[k] = '\0'; // ¡CRÍTICO!
            } 
            else {
                if (strlen(palabra) >= 2) {
                    if (strcmp(palabra, final) < 0) {
                        strcpy(final, palabra);
                    }
                }
                k = 0;
                limpiar_palabra(columnas + 1, palabra);
            }
        }
    }

    printf("%s", final);
    return 0;
}