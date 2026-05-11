#include <stdio.h>

int main () {
    double espacio = 0, lower = 0, upper = 0, simbolo = 0, longitud = 0;
    char cadena[100001];
    scanf("%s", cadena);
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == '_') {
            espacio++;
        } else if (cadena[i] >= 'a' && cadena[i] <= 'z') {
            lower++;
        } else if (cadena[i] >= 'A' && cadena[i] <= 'Z') {
            upper++;
        } else {
            simbolo++;
        }
        longitud++;

    }
    printf("%.6f\n", (espacio/(longitud)));
    printf("%.6f\n", (lower/(longitud)));
    printf("%.6f\n", (upper/(longitud)));
    printf("%.6f\n", (simbolo/(longitud)));
    return 0;
}