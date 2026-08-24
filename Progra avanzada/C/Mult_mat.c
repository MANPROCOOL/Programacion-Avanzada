#include <stdio.h>
#include <assert.h>



void llenar_matriz (int f, int c, int m[f][c]) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &m[i][j]);
        }
    }
}

void multiplicar(int f1, int c1, int m1[f1][c1], int f2, int c2, int m2[f2][c2], int resultado[f1][c2]) {
    assert(c1 == f2);
    for (int i = 0; i < f1; i++) {
        for (int j = 0; j < c2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                resultado[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main() {
    int f1, f2, c1, c2;
    scanf("%d %d %d %d", &f1, &c1, &f2, &c2);
    if (c1 != f2) {
        printf("No se pueden multiplicar");
        return 10;
    }
    else {
        int m1[f1][c1], m2[f2][c2], resultado[f1][c2];
        llenar_matriz(f1, c1, m1);
        llenar_matriz(f2, c2, m2);
        multiplicar(f1,c1,m1,f2,c2,m2,resultado);
        for (int i = 0; i < f1; i++) {
            for (int j = 0; j < c2; j++) {
                printf("%d ", resultado[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}