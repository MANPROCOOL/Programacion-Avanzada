#include <stdio.h>

int main(){
    int n, m, reverse, unidad, decena, centena;
    scanf("%d%d", &n, &m);

    centena = (int)(n / 100);
    decena = (int)((n % 100) / 10);
    unidad = n % 10;
    n = unidad * 100 + decena * 10 + centena;
    centena = (int)(m / 100);
    decena = (int)((m % 100) / 10);
    unidad = m % 10;
    m = unidad * 100 + decena * 10 + centena;
    if (n > m) {
        reverse = n;
    }
    else {
        reverse = m;
    }
    printf("%d", reverse);
    return 0;
}