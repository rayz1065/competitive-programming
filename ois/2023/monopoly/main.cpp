#include <bits/stdc++.h>
#define MAXN 1005
#define MAXK 1005
#define MAXT 3

using namespace std;

typedef long long ll;

int n;
int cells[MAXN];
ll memo[MAXN][MAXK][MAXT];

ll solve (int cell, int rem_k, int rem_t) {
    if (rem_k == 0) return 0;
    if (rem_t == 0) return solve(cell, rem_k - 1, MAXT);
    if (memo[cell][rem_k][rem_t - 1] != LLONG_MIN >> 1) return memo[cell][rem_k][rem_t - 1];
    ll best = LLONG_MIN >> 1;
    for (int i = 2; i <= 12; i++) {
        int nxtc = (cell + i) % n;
        if (i % 2 == 0) {
            // roll again
            best = max(best, cells[nxtc] + solve(nxtc, rem_k, rem_t - 1));
        }
        if (i != 2 && i != 12) {
            // end turn
            best = max(best, cells[nxtc] + solve(nxtc, rem_k - 1, MAXT));
        }
    }
    return memo[cell][rem_k][rem_t - 1] = best;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            fill(memo[i][j], memo[i][j] + MAXT, LLONG_MIN >> 1);
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> cells[i];
    }
    cout << solve(0, k, MAXT) << "\n";
}
