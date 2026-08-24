#include <stdio.h>

int main () {
    int hora, minuto;
    scanf("%d%d", &hora, &minuto);
    if (hora == 0 && minuto < 45){
       printf("23 %d", minuto - 45 + 60); 
    }
    else if (minuto < 45) {
        printf("%d %d", hora - 1, minuto - 45 + 60);
    }
    else {
        printf("%d %d", hora, minuto - 45);
    }
    return 0;
}