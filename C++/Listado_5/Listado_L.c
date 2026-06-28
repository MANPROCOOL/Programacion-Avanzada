#include <stdio.h>
#include <string.h>

char alfa[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
int N_ALFA = 28;

int idx_char(char c) {
    for (int i = 0; i < N_ALFA; i++) if (alfa[i] == c) return i;
    return -1;
}

int main() {
    int n;
    while (scanf("%d ", &n) == 1 && n != 0) {
        char s[45];
        scanf("%s", s);
        int len = strlen(s);
        // revertir
        for (int i = 0; i < len / 2; i++) {
            char tmp = s[i]; s[i] = s[len-1-i]; s[len-1-i] = tmp;
        }
        // rotar
        for (int i = 0; i < len; i++) {
            s[i] = alfa[(idx_char(s[i]) + n) % N_ALFA];
        }
        printf("%s\n", s);
    }
    return 0;
}