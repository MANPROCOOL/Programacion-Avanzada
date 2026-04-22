#include <stdio.h>

int main () {
    int cantidad = 0, bandera = 1;
    char cadena[1001], dice[12] = "Simon says", resultado[1001];
    scanf("%d", &cantidad);
    getchar(); // Limpia el buffer

    while (cantidad != 0) {
        int j = 0; 
        fgets(cadena, 1001, stdin);
        for (int i = 0; cadena[i] != '\0' && cadena[i] != '\n'; i++) {
            if (i < 10 && cadena[i] != dice[i]) {
                bandera = 0;
            }
            if (bandera == 1 && i > 10) {
                resultado[j] = cadena[i];
                j++;
            }
        }
        resultado[j] = '\0'; 

        if (bandera == 1) {
            printf("%s\n", resultado);
        }
        bandera = 1;
        cantidad--;
    }
    return 0;
}