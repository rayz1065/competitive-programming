#include <bits/stdc++.h>
#define MAXN 505
#define MAXV (MAXN * MAXN)
#define MODV 1000000007
#define MOD(x) ((x) % MODV)

using namespace std;

typedef long long ll;

int n, x;
int memo[MAXN][MAXV];

int sum_of_first_n(int n) { return n * (n + 1) / 2; }

int fast_exp(int base, int power) {
    if (power == 0) {
        return 1;
    }
    int res = fast_exp(base, power / 2);
    if (power % 2) {
        return MOD(MOD((ll)res * res) * base);
    }
    return MOD((ll)res * res);
}

int mod_inv(int x) { return fast_exp(x, MODV - 2); }

int solve(int i, int j) {
    if (j == x) {
        return 1;
    } else if (j > x || i == n) {
        return 0;
    } else if (memo[i][j]) {
        return memo[i][j] - 1;
    }

    int res = MOD(solve(i + 1, j) + solve(i + 1, j + i + 1));
    memo[i][j] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    x = sum_of_first_n(n);
    if (x % 2) {
        cout << "0\n";
        return 0;
    }
    x /= 2;

    int res = solve(0, 0);
    res = MOD((ll)mod_inv(2) * res);
    cout << res << "\n";
}
