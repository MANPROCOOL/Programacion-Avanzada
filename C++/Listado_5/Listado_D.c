#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);

        int slots[14];
        int q[200], qf = 0, qb = 0;
        for (int i = 1; i <= n; i++) q[qb++] = i;

        for (int carta = 1; carta <= n; carta++) {
            for (int m = 0; m < carta; m++) q[qb++] = q[qf++]; // mueve al fondo
            slots[q[qf++]] = carta; // asigna valor al slot que queda expuesto
        }

        for (int i = 1; i <= n; i++) {
            printf("%d", slots[i]);
            if (i < n) printf(" ");
        }
        printf("\n");
    }
    return 0;
}