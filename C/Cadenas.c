#include <stdio.h>

int main () {
    char cadena[100];
    printf("Ingrese una cadena de texto: ");
    fgets(cadena, 101, stdin);
    printf("La cadena ingresada es: %s", cadena);
    //haya el largo de la cadena de texto
    int largo = 0;
    while (cadena[largo] != '\0') {
        largo++;
    }
    largo -= 1;
    printf("El largo de la cadena es: %d", largo);
    return 0;
}