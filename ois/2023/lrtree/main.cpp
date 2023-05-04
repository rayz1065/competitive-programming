#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 1000005

using namespace std;

typedef long long ll;

int factorials[MAXN * 2];

int fast_exp (int x, int y) {
    if (y == 0) {
        return 1;
    }
    ll s = fast_exp(x, y / 2);
    s = (s * s) % MOD;
    s = (s * (y % 2 == 1 ? x : 1)) % MOD;
    return s;
}

int mod_inverse (int x) {
    return fast_exp(x, MOD - 2);
}

void precompute_factorials (int n) {
    factorials[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        factorials[i] = ((ll) factorials[i - 1] * i) % MOD;
    }
}

// (2n)! / ((n + 1)! * n!)
int catalan (int n) {
    ll res = factorials[2 * n];
    res = (res * mod_inverse(factorials[n + 1])) % MOD;
    res = (res * mod_inverse(factorials[n])) % MOD;
    return res;
}

int main () {
    int n;
    cin >> n;
    precompute_factorials(n);

    ll s = catalan(n);
    if (n % 2 == 1) {
        s = (s + MOD - catalan(n / 2)) % MOD;
    }
    s = (s * mod_inverse(2)) % MOD;
    cout << s << "\n";
}
