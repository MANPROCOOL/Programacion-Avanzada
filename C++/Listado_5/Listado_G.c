#include <stdio.h>
#include <string.h>

int main() {
    char s[305];
    scanf("%s", s);
    int n = strlen(s);
    char per[3] = {'P', 'E', 'R'};
    int dias = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != per[i % 3]) dias++;
    }
    printf("%d\n", dias);
    return 0;
}