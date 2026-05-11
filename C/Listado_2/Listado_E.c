#include <stdio.h>

int main() {
    int residuos[42] = {0};
    int num, i, distintos = 0;
    for (i = 0; i < 10; i++) {
        if (scanf("%d", &num) == 1) {
            residuos[num % 42] = 1;
        }
    }

    for (i = 0; i < 42; i++) {
        distintos += residuos[i];
    }
    printf("%d\n", distintos);
    return 0;
}