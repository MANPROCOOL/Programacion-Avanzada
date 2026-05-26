    #include <stdio.h>

    int recursive(int iter, int a, int b, int c) {

        if (iter == 1) return a;
        else if (iter == 2) return b;
        else if (iter == 3) return c;
        else {
            return (recursive(iter - 1, a, b, c) + recursive(iter - 2, a, b, c) + recursive(iter - 3, a, b, c));
        }

    }

    int main() {

        int cuanto, a, b, c;
        scanf("%d", &cuanto);
        scanf("%d %d %d", &a, &b, &c);
        printf("%d", recursive(cuanto, a, b, c));
    }