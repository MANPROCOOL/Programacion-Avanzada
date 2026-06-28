#include <stdio.h>

int main() {
    int vistos[10];
    int count = 0;

    for (int i = 0; i < 10; i++) {
        int x;
        scanf("%d", &x);
        int mod = x % 42;

        int encontrado = 0;
        for (int j = 0; j < count; j++) {
            if (vistos[j] == mod) encontrado = 1;
        }
        if (!encontrado) vistos[count++] = mod;
    }

    printf("%d\n", count);
    return 0;
}