#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // consume newline

    while (n--) {
        char linea[105];
        fgets(linea, 105, stdin);

        int visto[26] = {0};
        for (int i = 0; linea[i] != '\0'; i++) {
            char c = linea[i];
            if (c >= 'a' && c <= 'z') visto[c - 'a'] = 1;
            if (c >= 'A' && c <= 'Z') visto[c - 'A'] = 1;
        }

        int falta = 0;
        for (int i = 0; i < 26; i++) {
            if (!visto[i]) falta = 1;
        }

        if (!falta) {
            printf("pangram\n");
        } else {
            printf("missing ");
            for (int i = 0; i < 26; i++) {
                if (!visto[i]) printf("%c", 'a' + i);
            }
            printf("\n");
        }
    }
    return 0;
}