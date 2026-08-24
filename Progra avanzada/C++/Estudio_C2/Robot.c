#include <stdio.h>

// Verifica si es válido moverse a la derecha
int derecha(int fil, int col, int x, int y, char tablero[fil][col]){
    if (x + 1 >= col || tablero[y][x+1] == '#') { return 0; }
    return 1;
}

// Verifica si es válido moverse hacia abajo
int abajo(int fil, int col, int x, int y, char tablero[fil][col]){
    if (y + 1 >= fil || tablero[y+1][x] == '#') { return 0; }
    return 1;
}

int recursiva(int filas, int columnas, char tablero[filas][columnas], int actualx, int actualy){
    // Si la celda actual es un obstáculo, no hay caminos posibles desde aquí
    if (tablero[actualy][actualx] == '#') { return 0; }

    // ¡Llegamos a la meta! (esquina inferior derecha)
    if (actualx == columnas - 1 && actualy == filas - 1) { return 1; }
    
    int down = 0, der = 0;
    
    // Intentar ir hacia abajo
    if (abajo(filas, columnas, actualx, actualy, tablero)) {
        down = recursiva(filas, columnas, tablero, actualx, actualy + 1);
    }
    
    // Intentar ir hacia la derecha
    if (derecha(filas, columnas, actualx, actualy, tablero)) {
        der = recursiva(filas, columnas, tablero, actualx + 1, actualy);
    }
    
    // La suma de caminos de ambas decisiones
    return down + der;
}

int main() {
    int filas, columnas;
    
    // Leer dimensiones
    if (scanf("%d %d", &filas, &columnas) != 2) {
        return 1;
    }
    
    char tablero[filas][columnas];
    
    // Leer el tablero (ignorando espacios y saltos de línea)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // El espacio antes de %c hace que scanf ignore espacios/enters
            scanf(" %c", &tablero[i][j]); 
        }
    }
    
    // Calcular caminos desde el inicio (0,0)
    int caminos = recursiva(filas, columnas, tablero, 0, 0);
    
    printf("Output:\n%d\n", caminos);
    
    return 0;
}