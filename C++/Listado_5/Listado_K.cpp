#include <iostream>
#include <vector>
using namespace std;

void imprimir(const vector<int>& a) {
    for (int i = 0; i < 5; i++) { cout << a[i]; if (i < 4) cout << " "; }
    cout << "\n";
}

bool ordenado(const vector<int>& a) {
    for (int i = 0; i < 4; i++) if (a[i] > a[i+1]) return false;
    return true;
}

int main() {
    vector<int> a(5);
    for (int i = 0; i < 5; i++) cin >> a[i];
    while (!ordenado(a)) {
        for (int i = 0; i < 4; i++) {
            if (a[i] > a[i+1]) { swap(a[i], a[i+1]); imprimir(a); }
        }
    }
}