#include <stdio.h>

int main () {
    int size, largo, ancho, a,b,c,d, bigger;
    scanf("%d%d%d", &size, &largo, &ancho);
    a = largo * ancho * 4;
    b = (size - largo) * ancho * 4;
    c = largo * (size - ancho) * 4; 
    d = (size - largo) * (size - ancho) * 4;
    bigger = -1;
    if (a > bigger) {
        bigger = a;
    }
    if (b > bigger) {
        bigger = b;
    }
    if (c > bigger) {
        bigger = c;
    }
    if (d > bigger) {
        bigger = d;
    }
    printf("%d", bigger);

    return 0;
}