#include <stdio.h>

int main() {
    double x, y, t;
    
    scanf("%lf %lf", &x, &y);

    if (y == 1) {
        if (x == 0) {
            printf("ALL GOOD");
        } else {
            printf("IMPOSSIBLE");
        }
    } 
    else {
        t = x / (1.0 - y);
        printf("%.9f\n", t);
    }

    return 0;
}