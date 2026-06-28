#include <stdio.h>

void imprimir(int a[5]) {
    for (int i = 0; i < 5; i++) {
        printf("%d", a[i]);
        if (i < 4) printf(" ");
    }
    printf("\n");
}

int ordenado(int a[5]) {
    for (int i = 0; i < 4; i++) if (a[i] > a[i+1]) return 0;
    return 1;
}

int main() {
    int a[5];
    for (int i = 0; i < 5; i++) scanf("%d", &a[i]);
    while (!ordenado(a)) {
        for (int i = 0; i < 4; i++) {
            if (a[i] > a[i+1]) {
                int tmp = a[i]; a[i] = a[i+1]; a[i+1] = tmp;
                imprimir(a);
            }
        }
    }
    return 0;
}