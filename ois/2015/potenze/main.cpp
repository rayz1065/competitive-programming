#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    int n;
    cin >> n;
    ll best = 1;
    for (int i = 2; (ll) i * i <= n; i++) {
        for (ll curr = i * i; curr <= n; curr *= i) {
            best = max(best, curr);
        }
    }
    cout << best << "\n";
}
