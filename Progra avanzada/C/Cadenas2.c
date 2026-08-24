#include <stdio.h>
#include <string.h>

int main () {
    char nombre[101], apellido[101];
    printf("Ingrese su nombre: ");
    fgets(nombre, 101, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';
    printf("Ingrese su apellido: ");
    fgets(apellido, 101, stdin);
    strcat(nombre, " ");
    strcat(nombre, apellido);
    printf("Su nombre completo es: %s\n", nombre);

    return 0;
}