#include <iostream>
#include <string>
using namespace std;

int main() {
    string alfa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
    int N;
    while (cin >> N && N != 0) {
        string s; cin >> s;

        // revertir manual
        int len = s.size();
        for (int i = 0; i < len / 2; i++) swap(s[i], s[len-1-i]);

        // rotar
        for (char& c : s) {
            int idx = alfa.find(c);
            c = alfa[(idx + N) % 28];
        }
        cout << s << "\n";
    }
}