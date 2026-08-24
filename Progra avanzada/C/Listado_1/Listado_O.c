#include <stdio.h>

int main(){
    int a,b,c,d, small1, small2,x,y,z;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    small1 = -1;
    small2 = -1;
    if (a <= b && a <= c && a <= d) {
        small1 = a;
        x = b, y = c, z = d;
    }
    else if (b <= a && b <= c && b <= d) {
        small1 = b;
        x = a, y = c, z = d;
    }
    else if (c <= a && c <= b && c <= d) {
        small1 = c;
        x = a, y = b, z = d;
    }
    else {
        small1 = d;
        x = a, y = b, z = c;
    }
    if ((x >= y && x <= z) || (x <= y && x >= z)) {
        small2 = x;
    }
    else if ((y >= x && y <= z) || (y <= x && y >= z)) {
        small2 = y;
    }
    else {
        small2 = z;
    }
    printf("%d", small1 * small2);

    return 0;
}