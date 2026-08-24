#include <stdio.h>

void limpiar_cadena(int cantidad, int cadena[cantidad]) {
    for (int i = 0; i < cantidad; i++) {
        cadena[i] = 0;
    }
}

int main() {
    int n, final = 0, temp;
    scanf("%d", &n);
    int total[1001];
    limpiar_cadena(1001, total);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        total[temp] = 1;
    }

    for (int i = 1; i < 1001; i++) {
        if (total[i] == 1) {
            int inicio = i;
            final = i;

            while (final + 1 < 1001 && total[final + 1] == 1) {
                final++;
            }

            if (final >= inicio + 2) { // Si hay mas de 2
                printf("%d-%d ", inicio, final);
            } 
            else if (final == inicio + 1) {// Si hay exactamente dos
                printf("%d %d ", inicio, final);
            } 
            else {// Si hay solo uno
                printf("%d ", inicio);
            }
            i = final;
        }
    }
    printf("\n");
    return 0;
}