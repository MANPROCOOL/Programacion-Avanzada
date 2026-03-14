#include <stdio.h>

int main () {
    int l, r, bigger;
    scanf("%d%d", &l, &r);
    if (l == 0 && r == 0) {
        printf("Not a moose");
    } 
    else if ((l != r)) {
        bigger = -1;
        if (l > bigger) {
            bigger = l;
        }
        if (r > bigger) {
            bigger = r;
        }
        printf("Odd %d", 2*bigger);
    }
    else {
         printf("Even %d", 2*l);
    }
    return 0;
}