#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 1005

using namespace std;

int n;
char grid[MAXN][MAXN];
int memo[MAXN][MAXN];

bool in_range(int r, int c) { return r >= 0 && c >= 0 && r < n && c < n; }

int solve(int r, int c) {
    if (!in_range(r, c) || grid[r][c] == '*') {
        return 0;
    } else if (r == n - 1 && c == n - 1) {
        return 1;
    } else if (memo[r][c]) {
        return memo[r][c] - 1;
    }

    int res = (solve(r + 1, c) + solve(r, c + 1)) % MOD;

    memo[r][c] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    cout << solve(0, 0) << "\n";
}
