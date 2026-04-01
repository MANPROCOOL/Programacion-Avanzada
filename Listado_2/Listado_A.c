#include <stdio.h>

int main () {
    int n, m = 0;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++){
        if (a[i] < 0) {
            m ++;
        }
    }
    printf("%d", m);
    return 0;
}