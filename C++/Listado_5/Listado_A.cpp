#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp_col(const vector<string>& mat, int a, int b) {
    for (int i = 0; i < (int)mat.size(); i++) {
        char ca = tolower(mat[i][a]), cb = tolower(mat[i][b]);
        if (ca != cb) return ca < cb;
    }
    return false;
}

int main() {
    int r, c;
    bool primero = true;
    while (cin >> r >> c && (r || c)) {
        vector<string> mat(r);
        for (int i = 0; i < r; i++) cin >> mat[i];

        vector<int> cols(c);
        for (int i = 0; i < c; i++) cols[i] = i;
        stable_sort(cols.begin(), cols.end(), [&](int a, int b) {
            return cmp_col(mat, a, b);
        });

        if (!primero) cout << "\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) cout << mat[i][cols[j]];
            cout << "\n";
        }
        primero = false;
    }
}