#include <stdio.h>

int main () {

    int total = 0, jugada;
    char cadena[4], palo;
    scanf("%d %c", &jugada, &palo);
    for (int i = 0; i < jugada * 4; i++){
        scanf("%s", &cadena);
        if (cadena[0] == 'A') total += 11;
        if (cadena[0] == 'K') total += 4;
        if (cadena[0] == 'Q') total += 3;
        if (cadena[0] == 'J' && cadena[1] == palo) total += 20;
        if (cadena[0] == 'J' && cadena[1] != palo) total += 2;
        if (cadena[0] == 'T') total += 10;
        if (cadena[0] == '9' && cadena[1] == palo) total += 14;
    }

    printf("%d", total);

    return 0;
}