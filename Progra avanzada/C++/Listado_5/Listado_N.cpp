#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> s, b;
long long mejor;

void backtrack(int i, long long prod, long long suma, int elegidos) {
    if (i == n) {
        if (elegidos == 0) return;
        long long diff = prod - suma;
        if (diff < 0) diff = -diff;
        if (diff < mejor) mejor = diff;
        return;
    }
    backtrack(i + 1, prod, suma, elegidos);
    backtrack(i + 1, prod * s[i], suma + b[i], elegidos + 1);
}

int main() {
    cin >> n;
    s.resize(n); b.resize(n);
    for (int i = 0; i < n; i++) cin >> s[i] >> b[i];

    mejor = 2e18;
    backtrack(0, 1, 0, 0);
    cout << mejor << "\n";
}