#include <iostream>
#include <string>
using namespace std;

int main() {
    string s, res;
    cin >> s;
    for (char c : s) {
        if (c == '<') { if (!res.empty()) res.pop_back(); }
        else          res += c;
    }
    cout << res << "\n";
}