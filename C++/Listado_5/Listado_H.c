#include <stdio.h>
#include <string.h>

#define MAXN 100005

char nom[MAXN][21];
int ano[MAXN];
char tmp_nom[MAXN][21];
int tmp_ano[MAXN];
int n;

void merge_sort(int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    merge_sort(l, m);
    merge_sort(m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        int cmp = strcmp(nom[i], nom[j]);
        if (cmp < 0 || (cmp == 0 && ano[i] <= ano[j])) {
            tmp_ano[k] = ano[i]; strcpy(tmp_nom[k], nom[i]); i++;
        } else {
            tmp_ano[k] = ano[j]; strcpy(tmp_nom[k], nom[j]); j++;
        }
        k++;
    }
    while (i < m) { tmp_ano[k] = ano[i]; strcpy(tmp_nom[k], nom[i]); i++; k++; }
    while (j < r) { tmp_ano[k] = ano[j]; strcpy(tmp_nom[k], nom[j]); j++; k++; }
    for (int x = l; x < r; x++) { ano[x] = tmp_ano[x]; strcpy(nom[x], tmp_nom[x]); }
}

// Busqueda binaria: primer indice del pais
int lower_bound(char *pais) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (strcmp(nom[mid], pais) < 0) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s %d", nom[i], &ano[i]);

    // Ordenar por nombre, luego por anio (estable para mismo pais)
    merge_sort(0, n);

    int q;
    scanf("%d", &q);
    while (q--) {
        char pais[21];
        int k;
        scanf("%s %d", pais, &k);
        int idx = lower_bound(pais) + k - 1; // k-esimo viaje del pais
        printf("%d\n", ano[idx]);
    }
    return 0;
}