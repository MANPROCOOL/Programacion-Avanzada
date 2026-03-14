#include <stdio.h>

int main () {
    int gold, silver, copper, total;
    scanf("%d%d%d", &gold, &silver, &copper);
    total = gold * 3 + silver * 2 + copper;
    if (total >= 8) {
        printf("Province or Gold");
    }
    else if (total >= 6){
        printf("Duchy or Gold");
    }
    else if (total >= 5) {
            printf("Duchy or Silver");
    }
    else if (total >= 3) {
            printf("Estate or Silver");
    }
    else if (total >= 2) {
            printf("Estate or Copper");
    }
    else {
        printf("Copper");
    }
    return 0;
}