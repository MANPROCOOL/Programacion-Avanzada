#include <iostream>
using namespace std;

int suma_digitos(long long x) {
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

int main() {
    int N;
    while (cin >> N && N != 0) {
        int sd = suma_digitos(N);
        int p = 11;
        while (suma_digitos((long long)N * p) != sd) p++;
        cout << p << "\n";
    }
}