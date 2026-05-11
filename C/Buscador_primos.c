#include <stdio.h>
#include <math.h>

int main () {
    long current, hasta;
    int divisor;
    double raiz;
    scanf("%ld %ld", &current, &hasta);
    if (current == 1 || current == 2) printf("%d ", 2);
    if (current % 2 == 0) (current += 1);
    while (current <= hasta) {
        raiz = sqrt(current);
        if (raiz == (int)raiz) (current += 2);
        else {
            divisor = 3;
            while (current % divisor != 0 && divisor <= raiz) {
                divisor += 2;
            }
            if (divisor > raiz) (printf("%ld ", current));
            current += 2;
        } 
    }
    return 0;
}