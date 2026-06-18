#include <stdio.h>

// declaración sin uso:
int a(int n);

int b(int n){
    if (n < 10)
        return n;
    if (n%2){
        return b(n - 5);
    }
    return a(n);
}

int a(int n){
    if (n < 10)
        return n;
    if (n%2 == 0){
        return a(n - 17);
    }
    return b(n);
}

int main(){
    int n;
    scanf("%d", &n);
    printf("from %d to %d\n", n, b(n));

    return 1;
}
