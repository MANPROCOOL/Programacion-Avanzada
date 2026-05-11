#include <stdio.h>

void limpiar_matriz_cuadrada(int n, int matriz[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }  
}

void limpiar_arreglo(int n, int arreglo[n]) {
    for (int i = 0; i < n; i++) {
        arreglo[i] = 0;
    }
}

void bfs(int n, int matriz[n][n], int *distancias, int origen) {
    int fila[n], agregados[n];
    int next = 0, tam = 0;
    limpiar_arreglo(n, fila), limpiar_arreglo(n, agregados);
    fila[0] = origen, agregados[origen] = 1;
    tam++;
    while (next < tam) {
        int sig = fila[next];
        for (int i = 0; i < n; i++) {
            if (matriz[sig][i] == 1 && agregados[i] == 0) {
                fila[tam] = i, agregados[i] = 1;
                distancias[i] = distancias[sig] + 1;
                tam++;
                
            }
        }
        next++;
    }
}

int main () {
    int n, m;
    scanf("%d %d", &n, &m);
    int matriz[n][n];
    limpiar_matriz_cuadrada(n, matriz);

    for (int i = 0; i <m ; i++) {
        int n1, n2;
        scanf("%d %d", &n1, &n2);
        matriz[n1][n2] = 1;
        matriz[n2][n1] = 1;
    }

    int distancias[n];
    limpiar_arreglo(n, distancias);
    int origen = 0;
    bfs(n, matriz, distancias, origen);
    
    return 0;
}