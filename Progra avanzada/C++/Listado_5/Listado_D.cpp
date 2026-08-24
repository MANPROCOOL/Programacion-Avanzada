#include <iostream>
#include <queue>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        queue<int> q;
        for (int i = 1; i <= n; i++) q.push(i);

        vector<int> slots(n + 1);
        for (int carta = 1; carta <= n; carta++) {
            for (int m = 0; m < carta; m++) { q.push(q.front()); q.pop(); }
            slots[q.front()] = carta; q.pop();
        }
        for (int i = 1; i <= n; i++) {
            cout << slots[i];
            if (i < n) cout << " ";
        }
        cout << "\n";
    }
}