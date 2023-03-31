#include <bits/stdc++.h>

using namespace std;

bool tc () {
    int n, r, t;
    cin >> n >> r >> t;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int s_i;
        cin >> s_i;
        sum += s_i;
    }
    bool cheater = sum > (r + t) * n;
    // cerr << sum << "/" << n << " >? " << r + t << "\n";
    return cheater ? 1 : 0;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cout << (tc() ? "Cheater" : "Innocent") << "\n";
    }
}