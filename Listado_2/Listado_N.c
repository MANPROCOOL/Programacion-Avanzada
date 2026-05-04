#include <stdio.h>

int main () {
    char adrian[13] = "ABCABCABCABC", bruno[13] = "BABCBABCBABC", goran[13] = "CCAABBCCAABB", cadena[100001];
    int cant = 0, adrian_score = 0, bruno_score = 0, goran_score = 0, max_score = -1, j = 0;
    scanf("%d", &cant);
    scanf("%s", cadena);
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == adrian[j]) {
            adrian_score++;
        }
        if (cadena[i] == bruno[j]) {
            bruno_score++;
        }
        if (cadena[i] == goran[j]) {
            goran_score++;
        }
        if (j == 12) {
            j = -1;
        }
        j++;
        }
    max_score = adrian_score;
    if (bruno_score > max_score) {
        max_score = bruno_score;
    }
    if (goran_score > max_score) {
        max_score = goran_score;
    }
    printf("%d\n", max_score);
    if (adrian_score == max_score) {
        printf("Adrian\n");
    }
    if (bruno_score == max_score) {
        printf("Bruno\n");
    }
    if (goran_score == max_score) {
        printf("Goran\n");
    }

    return 0;
}