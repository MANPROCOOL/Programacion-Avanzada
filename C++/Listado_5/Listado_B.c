#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int total = 2 * n;

    int *og  = (int *)malloc(total * sizeof(int));
    int *aux = (int *)malloc(total * sizeof(int));
    for (int i = 0; i < total; i++) scanf("%d", &og[i]);

    int top_og = 0, top_aux = 0, pares = 0;
    long long movs = 0;

    while (top_og < total) {
        if (top_aux > 0 && og[top_og] == aux[top_aux - 1]) {
            pares++;
            movs++;
            top_og++;
            top_aux--;
        } else {
            aux[top_aux++] = og[top_og++]; // mov1: og -> aux
            movs++;
        }
    }

    if (pares == n) printf("%lld\n", movs);
    else            printf("impossible\n");

    free(og);
    free(aux);
    return 0;
}