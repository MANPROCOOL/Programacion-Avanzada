#include <stdio.h>

void rotar(int matriz[4][4]) {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = matriz[j][i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz[i][j] = temp[i][j];
        }
    }
}

void reflejar(int matriz[4][4]) {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = matriz[i][3 - j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz[i][j] = temp[i][j];
        }
    }
}

void imprimir(int matriz[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void sumar(int matriz[4][4]){
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++){ // Llego hasta el 3 porque si tomo el 4 suma entre filas
            if (matriz[j][i] == matriz[j][i+1]){
                matriz[j][i] += matriz[j][i+1];
                matriz[j][i+1] = 0;
            }
        }
    }
}

void mover(int matriz[4][4]){
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (matriz[j][i] == 0) {
                matriz[j][i] = matriz[j][i+1];
                matriz[j][i+1] = 0;
            }
        }
    }
}



int main () { 
    int matriz[4][4], mov;
    scanf("%d %d %d %d", &matriz[0][0], &matriz[0][1], &matriz[0][2], &matriz[0][3]);
    scanf("%d %d %d %d", &matriz[1][0], &matriz[1][1], &matriz[1][2], &matriz[1][3]);
    scanf("%d %d %d %d", &matriz[2][0], &matriz[2][1], &matriz[2][2], &matriz[2][3]);
    scanf("%d %d %d %d", &matriz[3][0], &matriz[3][1], &matriz[3][2], &matriz[3][3]);
    scanf("%d", &mov);
    if (mov == 0) {
        mover(matriz), mover(matriz), sumar(matriz), mover(matriz), mover(matriz), mover(matriz);
    }
    else if (mov == 1) {
        rotar(matriz), mover(matriz), mover(matriz), sumar(matriz), mover(matriz), mover(matriz), mover(matriz), rotar(matriz);
    }
    else if (mov == 2) {
        reflejar(matriz), mover(matriz), mover(matriz), sumar(matriz), mover(matriz), mover(matriz), mover(matriz), reflejar(matriz);
    }
    else if (mov == 3) {
        rotar(matriz), reflejar(matriz), mover(matriz), mover(matriz), sumar(matriz), mover(matriz), mover(matriz), mover(matriz), reflejar(matriz), rotar(matriz);
    }
    imprimir(matriz);
    
    return 0;
}
