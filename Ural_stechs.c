#include <stdio.h>
#include <math.h>

int main () {
    int capacidad, lomos;

    scanf("%d %d", &capacidad, &lomos);
    
    if (lomos <= capacidad) {
        printf("2\n");
    }
    else {
        int tiempo = (int)ceil((double)(lomos * 2) / capacidad); 
        printf("%d\n", tiempo);
    }
    return 0;
}