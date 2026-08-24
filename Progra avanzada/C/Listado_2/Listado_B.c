    #include <stdio.h>

    int main () {
        int n, m, restante = 0, p = 0;
        scanf("%d", &n);
        scanf("%d", &m);
        restante = n;
        for (int i = 0; i < m; i++) {
            restante += n;
            scanf("%d", &p);
            if (restante > p) restante -= p;
            else restante = 0;
        }
        printf("%d", restante);
        return 0;
    }