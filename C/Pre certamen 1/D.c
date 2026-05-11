#include <stdio.h>
void limpiar(int filas, int columnas, int matriz[filas][columnas]){
    for (int i = 0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            matriz[i][j] = 0;
        }
    }
}


int main () {

    int registros = 0;
    while (registros != -1){
        scanf("%d", &registros);
        int cadena[registros + 2][3], total = 0;
        limpiar(registros + 2, 3, cadena);
        for (int i = 0; i < registros; i++) {
            scanf("%d %d", &cadena[i + 1][0], &cadena[i + 1][1]);
        }
        for (int i = 1; i < registros + 1; i++) {
            total += cadena[i][0] * (cadena[i][1] - cadena[i - 1][1]);
        }
        if (registros != -1) printf("%d miles\n", total);
    }


    return 0;
}