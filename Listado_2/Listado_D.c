#include <stdio.h>

int main () {
    int cases, previo, actual, sum = 0, i = 0;
    scanf("%d", &cases);
    while (i < cases) {
        scanf("%d", &actual);
        while (actual != 0) {
            previo = actual + 0;
            scanf("%d", &actual);
            if (actual > 2 * previo){
                sum = sum + actual - 2 * previo;
            }
        }
        printf("%d\n", sum);
        sum = 0, i++;

    }
    return 0;
}