#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    long long s[10], b[10];
    for (int i = 0; i < n; i++) scanf("%lld %lld", &s[i], &b[i]);

    long long mejor = -1;
    for (int mask = 1; mask < (1 << n); mask++) {
        long long prod = 1, suma = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { prod *= s[i]; suma += b[i]; }
        }
        long long diff = prod - suma;
        if (diff < 0) diff = -diff;
        if (mejor == -1 || diff < mejor) mejor = diff;
    }
    printf("%lld\n", mejor);
    return 0;
}