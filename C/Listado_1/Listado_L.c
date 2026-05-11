#include <stdio.h>

int main () {
    int n;
    scanf("%d", &n);
    if (n <= 3) {
        printf("%d",1);
    }
    else {
        printf("%d", n - 2);
    }
    return 0;
}