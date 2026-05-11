#include <stdio.h>

int main () {
    char first[501], second[501], resultado[501];
    int cant = 0;  
    scanf("%d", &cant);
    while (cant != 0) {
        scanf("%s %s", first, second);
        for (int i = 0; first[i] != '\0'; i++) {
            if (first[i] == second[i]) {
                resultado[i] = '.';
            } else {
                resultado[i] = '*';
            }
            if (first[i+1] == '\0') {
                resultado[i+1] = '\0';
            }   
        }
        printf("%s\n", first);
        printf("%s\n", second);
        printf("%s\n", resultado);
        cant--;
    }
    return 0;
}