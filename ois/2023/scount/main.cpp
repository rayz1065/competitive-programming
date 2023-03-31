#include <bits/stdc++.h>
#define MAXN 100005
#define MOD 1000000007

using namespace std;

typedef long long ll;

int fact[MAXN];

int mod_inverse(int A, int M) {
    int m0 = M;
    int y = 0, x = 1;
    if (M == 1) return 0;
    while (A > 1) {
        int q = A / M;
        int t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

int cnk (int n, int k) {
    return (((ll) fact[n] * mod_inverse(fact[k], MOD)) % MOD
                          * mod_inverse(fact[n - k], MOD)) % MOD;
}

int main () {
    int n;
    cin >> n;
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = ((ll) fact[i - 1] * i) % MOD;
    }
    map<ll, int> freqs;
    for (int i = 0; i < n; i++) {
        ll v;
        cin >> v;
        freqs[v] += 1;
    }
    vector<int> sets_by_size(n + 1);
    sets_by_size[0] = 1;
    for (auto j: freqs) {
        for (int k = j.second; k >= 1; k--) {
            int new_ways = ((ll) cnk(j.second, k) * (1 + sets_by_size[k])) % MOD;
            sets_by_size[k] = (sets_by_size[k] + new_ways) % MOD;
        }
    }
    int total = 0;
    for (auto j: sets_by_size) {
        total = (total + j) % MOD;
        // cerr << j << " ";
    }
    // cerr << "\n";
    cout << total << "\n";
}
