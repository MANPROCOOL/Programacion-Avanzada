#include <stdio.h>

int main() {
    int n;
    char original[1001], final[1001];
    
    scanf("%d", &n);
    scanf("%s", original);
    scanf("%s", final);

    int exito = 1, bandera = 1;
    
    for(int i = 0; original[i] != '\0' && bandera; i++) {
        if (n % 2 != 0) { // N es impar: deben ser diferentes
            if (original[i] == final[i]) {
                exito = 0;
                bandera = 0;
            }
        } else { // N es par: deben ser iguales
            if (original[i] != final[i]) {  
                exito = 0;
                bandera = 0;
            }
        }
    }

    if (exito) printf("Deletion succeeded\n");
    else printf("Deletion failed\n");

    return 0;
}