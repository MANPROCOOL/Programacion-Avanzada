#include <stdio.h>

int main () {
    char cadena[31];
    int bandera = 0;
    scanf("%s", cadena);
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == 's' && cadena[i+1] == 's') {
            bandera = 1;
        }
    }
    if (bandera == 1) {
        printf("hiss\n");
    } else {
        printf("no hiss\n");
    }
    return 0;
}