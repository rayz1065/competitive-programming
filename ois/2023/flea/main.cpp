#include <bits/stdc++.h>

using namespace std;

int main () {
    int n;
    string moves;
    int s = 0;
    cin >> n >> moves;
    for (int i = 0; i < n; i++) {
        s += (moves[i] == 'L' ? 1 : -1);
    }
    cout << abs(s) << "\n";
}
