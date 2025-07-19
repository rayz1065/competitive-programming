#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 105
#define MOD 1000000007

using namespace std;

int n, m;
int values[MAXN];
int memo[MAXN][MAXM];

int solve(int i, int j) {
    if (j <= 0 || j > m) {
        return 0;
    } else if (i == n) {
        return 1;
    } else if (values[i] && abs(values[i] - j) > 1) {
        return 0;
    } else if (memo[i][j]) {
        return memo[i][j] - 1;
    }

    int res = 0;
    if (values[i]) {
        res = solve(i + 1, values[i]);
    } else {
        for (int k = 0; k < 3; k++) {
            res = (res + solve(i + 1, j + k - 1)) % MOD;
        }
    }

    memo[i][j] = res + 1;

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    int res = 0;
    if (values[0]) {
        res = solve(1, values[0]);
    } else {
        for (int j = 1; j <= m; j++) {
            res = (res + solve(1, j)) % MOD;
        }
    }

    cout << res << "\n";
}
