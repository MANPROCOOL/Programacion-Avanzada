#include <stdio.h>
#include <string.h>
 
int main() {
    char s[1000005];
    char resultado[1000005];
    int top = 0;
 
    scanf("%s", s);
    int n = strlen(s);
 
    for (int i = 0; i < n; i++) {
        if (s[i] == '<') {
            if (top > 0) top--; // backspace: elimina ultimo caracter
        } else {
            resultado[top++] = s[i];
        }
    }
    resultado[top] = '\0';
    printf("%s\n", resultado);
    return 0;
}