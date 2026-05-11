# include <stdio.h>

int main() {
    int filas = 1, columnas = 1, movs, mult, realx = 0, realy = 0, robotx = 0, roboty = 0;
    char direccion;
    while (filas != 0 && columnas != 0) {
        scanf("%d %d", &columnas, &filas);
            if (filas != 0 && columnas != 0) {
                realx = 0, realy = 0, robotx = 0, roboty = 0;
                scanf("%d", &movs);
                while (movs > 0) {
                    movs -= 1;
                    scanf(" %c %d", &direccion, &mult);
                    if (direccion == 'u') {
                        roboty += mult, realy += mult;
                        if (realy > filas - 1) realy = filas - 1;
                    }
                    if (direccion == 'd') {
                        roboty -= mult, realy -= mult;
                        if (realy < 0) realy = 0;
                    }
                    if (direccion == 'r') {
                        robotx += mult, realx += mult;
                        if (realx > columnas - 1) realx = columnas - 1;
                    }
                    if (direccion == 'l') {
                        robotx -= mult, realx -= mult;
                        if (realx < 0) realx = 0;
                    }
                }
            }
        if (filas != 0 && columnas != 0) {
        printf("Robot thinks %d %d\n", robotx, roboty);
        printf("Actually at %d %d\n", realx, realy);
        printf("\n");}
    }
    
    return 0;
}