#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> og(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> og[i];

    stack<int> aux;
    int top_og = 0, pares = 0;
    long long movs = 0;

    while (top_og < 2 * n) {
        if (!aux.empty() && og[top_og] == aux.top()) {
            pares++;
            movs++;
            top_og++;
            aux.pop();
        } else {
            aux.push(og[top_og++]);
            movs++;
        }
    }

    if (pares == n) cout << movs << "\n";
    else            cout << "impossible\n";
}