#include <stdio.h>
#include <string.h>

int cmp2(char *a, char *b) { // retorna 1 si a > b segun primeras 2 letras
    for (int i = 0; i < 2; i++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return 0;
    }
    return 0;
}

int main() {
    int n;
    int primero = 1;
    while (scanf("%d", &n) == 1 && n != 0) {
        char nombres[200][21];
        for (int i = 0; i < n; i++) scanf("%s", nombres[i]);

        // insertion sort estable por primeras 2 letras
        for (int i = 1; i < n; i++) {
            int j = i;
            while (j > 0 && cmp2(nombres[j-1], nombres[j])) {
                char buf[21];
                strcpy(buf, nombres[j]); strcpy(nombres[j], nombres[j-1]); strcpy(nombres[j-1], buf);
                j--;
            }
        }

        if (!primero) printf("\n");
        for (int i = 0; i < n; i++) printf("%s\n", nombres[i]);
        primero = 0;
    }
    return 0;
}