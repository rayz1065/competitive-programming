#include <bits/stdc++.h>
#define MAXN 5005

using namespace std;

int n, m;
string a, b;
int memo[MAXN][MAXN];

int solve(int i, int j) {
    if (i == n && j == m) {
        return 0;
    } else if (i == n) {
        return m - j;
    } else if (j == m) {
        return n - i;
    } else if (memo[i][j]) {
        return memo[i][j] - 1;
    }

    int res = INT_MAX >> 1;
    if (a[i] == b[j]) {
        res = solve(i + 1, j + 1);
    } else {
        res = min(res, solve(i + 1, j) + 1);
        res = min(res, solve(i, j + 1) + 1);
        res = min(res, solve(i + 1, j + 1) + 1);
    }

    memo[i][j] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> a >> b;
    n = a.length();
    m = b.length();

    cout << solve(0, 0) << "\n";
}
