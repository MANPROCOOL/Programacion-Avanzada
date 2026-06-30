#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    int n; cin >> n;
    cin.ignore();
    while (n--) {
        string linea;
        getline(cin, linea);
        set<char> visto;
        for (char c : linea) {
            if (c >= 'a' && c <= 'z') visto.insert(c);
            if (c >= 'A' && c <= 'Z') visto.insert(c - 'A' + 'a');
        }
        if ((int)visto.size() == 26) {
            cout << "pangram\n";
        } else {
            cout << "missing ";
            for (char c = 'a'; c <= 'z'; c++) if (!visto.count(c)) cout << c;
            cout << "\n";
        }
    }
}