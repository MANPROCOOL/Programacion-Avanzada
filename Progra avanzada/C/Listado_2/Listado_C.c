#include <stdio.h>

int main() {
    long long cont, copy, new, temp;
    int n = 1, p;
    while (n > 0) {
        scanf("%d", &n);
        copy = n;
        cont = 0;
        while (copy > 0) {
            cont = cont + copy % 10;
            copy /= 10;}
    p = 11, new = 0;
    while (new != cont){
        new = 0;
        temp = n * p;
        while (temp > 0) {
            new = new + temp % 10;
            temp /= 10;}
        p++;
    }
    if (n != 0) {
        printf("%d\n", (p-1));}
    }
    return 0;
}