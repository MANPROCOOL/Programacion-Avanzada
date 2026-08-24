#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; cin >> s;
    string per = "PER";
    int dias = 0;
    for (int i = 0; i < (int)s.size(); i++) if (s[i] != per[i % 3]) dias++;
    cout << dias << "\n";
}