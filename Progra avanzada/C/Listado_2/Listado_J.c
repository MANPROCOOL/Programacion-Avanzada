# include <stdio.h>

int main() {
    char cadena[101], resultado[101];
    int i = 0, j = 0, bandera = 1;
    scanf("%s", cadena);
    while (cadena[i] != '\0') {
        if (bandera == 1) {resultado[j] = cadena[i];
            j++;
            bandera = 0;
        } 
        if (cadena[i] == '-')   {
            bandera = 1;
        }
        i++;
    }
    resultado[j] = '\0';
    printf("%s\n", resultado);
    return 0;
}