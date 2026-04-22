#include <stdio.h>

int main () {
    char cadena[101], resultado[101];
    int j = 0;
    fgets(cadena, 101, stdin);
    for (int i = 0; cadena[i] != '\0'; i++) {
        if ((cadena[i] == 'a' || cadena[i] == 'e' || cadena[i] == 'i' || cadena[i] == 'o' || cadena[i] == 'u') && cadena[i+2] == cadena[i] && cadena[i+1] == 'p') {
            i += 2;
        }
        resultado[j] = cadena[i];
        j++;
    }
    resultado[j] = '\0';
    printf("%s", resultado);
    return 0;
}