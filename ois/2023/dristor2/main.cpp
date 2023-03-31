#include <bits/stdc++.h>
#define MAXN 14
#define MAXM 105
#define TTMAXN 17000
#define MOD 1000000007

using namespace std;

bool knows_spot[MAXN + 5][MAXM];
int memo[TTMAXN][MAXM];
int n, m;
int k;

int solve (bitset<MAXN> &used, int spot) {
    if (used.count() == k) {
        return 1;
    }
    if (spot >= m) return 0;
    if (memo[used.to_ulong()][spot] != -1) {
        return memo[used.to_ulong()][spot];
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i] && knows_spot[i][spot]) {
            used[i] = 1;
            s = (s + solve(used, spot + 1)) % MOD;
            used[i] = 0;
        }
    }
    s = (s + solve(used, spot + 1)) % MOD; // skip
    return memo[used.to_ulong()][spot] = s;
}

int main () {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> knows_spot[i][j];
        }
    }
    bitset<MAXN> used = {};
    for (k = n; k > 0; k--) {
        for (int i = 0; i < TTMAXN; i++) {
            fill(memo[i], memo[i] + m, -1);
        }
        if (solve(used, 0)) {
            break ;
        }
    }
    cout << solve(used, 0) << "\n";
}
