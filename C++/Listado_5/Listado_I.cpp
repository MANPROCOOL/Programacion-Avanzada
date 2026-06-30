#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; cin >> s;
    int es = s.size() - 2;
    cout << "h" << string(es * 2, 'e') << "y\n";
}   