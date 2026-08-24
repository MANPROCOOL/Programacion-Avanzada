#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> vistos;
    for (int i = 0; i < 10; i++) {
        int x; cin >> x;
        vistos.insert(x % 42);
    }
    cout << vistos.size() << "\n";
}