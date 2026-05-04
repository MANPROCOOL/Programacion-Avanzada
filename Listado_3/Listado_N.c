#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void limpiar(int cadena[3000]){
    for (int i = 0; i < 3000; i++) {
        cadena[i] = 0;
    }
}

int main() {
    int n;
    int cadena[3000], diferencias[3000];
    while (scanf("%d", &n) != EOF) {
        int jolly = 1, current = 0;
        limpiar(cadena), limpiar(diferencias);
        for (int i = 0; i < n; i++){
            scanf(" %d", &cadena[i]);
        }
        for (int i = 0; i < n - 1; i++) {
            current = abs(cadena[i] - cadena[i+1]);
            diferencias[current] = 1;
        }
        for (int i = 1; i < n; i++) {
            if (diferencias[i] == 0) jolly = 0;
        }
        if (jolly) printf("Jolly\n");
        else {printf("Not jolly\n");}    
    }
    return 0;
}