#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    bool primero = true;
    while (cin >> n && n != 0) {
        vector<string> nombres(n);
        for (int i = 0; i < n; i++) cin >> nombres[i];

        // insertion sort estable por primeras 2 letras (ASCII)
        for (int i = 1; i < n; i++) {
            int j = i;
            while (j > 0 && nombres[j-1].substr(0,2) > nombres[j].substr(0,2)) {
                swap(nombres[j], nombres[j-1]);
                j--;
            }
        }

        if (!primero) cout << "\n";
        for (const string& s : nombres) cout << s << "\n";
        primero = false;
    }
}