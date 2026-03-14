#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c, d, t;
    
    if (scanf("%d %d %d %d %d", &a, &b, &c, &d, &t) != 5) return 0;
    int distancia = abs(a - c) + abs(b - d);

    if (t >= distancia && (t - distancia) % 2 == 0) {
        printf("Y");
    } else {
        printf("N");
    }
    return 0;
}