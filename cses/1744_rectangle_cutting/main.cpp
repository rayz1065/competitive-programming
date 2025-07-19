#include <bits/stdc++.h>
#define MAXN 505
#define INF (INT_MAX >> 1)

using namespace std;

int memo[MAXN][MAXN];

int solve(int n, int m) {
    if (n < m) {
        swap(n, m);
    }

    if (n == m) {
        return 0;
    } else if (memo[n][m]) {
        return memo[n][m] - 1;
    }

    int res = INF;

    for (int i = 1; i <= n / 2; i++) {
        res = min(res, solve(i, m) + solve(n - i, m) + 1);
    }
    for (int i = 1; i <= m / 2; i++) {
        res = min(res, solve(n, i) + solve(n, m - i) + 1);
    }

    memo[n][m] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    cout << solve(n, m) << "\n";
}
