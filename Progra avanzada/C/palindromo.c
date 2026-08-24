#include <stdio.h>
#include <string.h>

int main () {
    char cadena[101], invertida[101];
    printf("Ingrese una cadena de texto: ");
    fgets(cadena, 101, stdin);
    // Eliminar el salto de línea al final de la cadena
    cadena[strcspn(cadena, "\n")] = '\0';
    int largo = strlen(cadena);
    // Invertir la cadena
    for (int i = 0; i < largo; i++) {
        invertida[i] = cadena[largo - 1 - i];
    }
    invertida[largo] = '\0';
    printf("La cadena invertida es: %s\n", invertida);
    if (strcmp(cadena, invertida) == 0) {   
        printf("La cadena es un palindromo.\n");
    } else {
        printf("La cadena no es un palindromo.\n");
    }

    return 0;
}