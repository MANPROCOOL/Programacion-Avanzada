#include <iostream>
#include <map>
#include <vector>
using namespace std;

void merge_sort(vector<int>& v, int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m, r);
    vector<int> tmp;
    int i = l, j = m;
    while (i < m && j < r) {
        if (v[i] <= v[j]) tmp.push_back(v[i++]);
        else               tmp.push_back(v[j++]);
    }
    while (i < m) tmp.push_back(v[i++]);
    while (j < r) tmp.push_back(v[j++]);
    for (int k = l; k < r; k++) v[k] = tmp[k - l];
}

int main() {
    int n; cin >> n;
    map<string, vector<int>> viajes;
    for (int i = 0; i < n; i++) {
        string pais; int anio;
        cin >> pais >> anio;
        viajes[pais].push_back(anio);
    }
    for (auto& p : viajes) merge_sort(p.second, 0, p.second.size());

    int q; cin >> q;
    while (q--) {
        string pais; int k;
        cin >> pais >> k;
        cout << viajes[pais][k - 1] << "\n";
    }
}