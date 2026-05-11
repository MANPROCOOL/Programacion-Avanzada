#include <stdio.h>

void check(char matriz[5][6], int *bandera) {
    int knight = 0; 
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++) {
            if (matriz[i][j] == 'k') {
                if (matriz[i-1][j-2] == 'k' && i-1 >= 0 && j-2 >= 0) *bandera = 1; // Todos los 8 posibles mov del caballo
                if (matriz[i-1][j+2] == 'k' && i-1 >= 0 && j+2 < 5) *bandera = 1; //comprueboi que no se mueva fuera del tablero
                if (matriz[i+1][j-2] == 'k' && i+1 < 5 && j-2 >= 0) *bandera = 1;
                if (matriz[i+1][j+2] == 'k' && i+1 < 5 && j+2 < 5) *bandera = 1;
                if (matriz[i-2][j-1] == 'k' && i-2 >= 0 && j-1 >= 0) *bandera = 1;
                if (matriz[i-2][j+1] == 'k' && i-2 >= 0 && j+1 < 5) *bandera = 1;
                if (matriz[i+2][j-1] == 'k' && i+2 < 5 && j-1 >= 0) *bandera = 1;
                if (matriz[i+2][j+1] == 'k' && i+2 < 5 && j+1 < 5) *bandera = 1;
                knight++;
            }
        }
    }
    if (knight != 9) *bandera = 1;
}

int main() {
    char matriz[5][6];
    int bandera = 0;
    scanf ("%s %s %s %s %s", matriz[0], matriz[1], matriz[2], matriz[3], matriz[4]);
    check(matriz, &bandera);
    if (bandera) printf("invalid");
    else printf("valid");
}