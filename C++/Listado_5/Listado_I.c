#include <stdio.h>
#include <string.h>

int main() {
    char s[1005];
    scanf("%s", s);
    int n = strlen(s);
    int es = n - 2; // cantidad de e's (s = "h" + e's + "y")
    printf("h");
    for (int i = 0; i < es * 2; i++) printf("e");
    printf("y\n");
    return 0;
}