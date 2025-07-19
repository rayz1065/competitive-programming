#include <bits/stdc++.h>
#define MAXN 11
#define MAXM 1005
#define POWMAXN 1030
#define MOD(x) ((x) % 1000000007)

using namespace std;

int n, m;
int memo[MAXM][MAXN][POWMAXN];

int solve(int m_idx, int n_idx, int flag) {
    if (m_idx == m) {
        return flag == 0;
    } else if (n_idx == n) {
        return solve(m_idx + 1, 0, (~flag) & ((1 << n) - 1));
    } else if (memo[m_idx][n_idx][flag]) {
        return memo[m_idx][n_idx][flag] - 1;
    }

    // skip
    int res = solve(m_idx, n_idx + 1, flag);

    // vertical tile
    int i_bit = 1 << n_idx;
    int in_bit = 1 << (n_idx + 1);
    if (n_idx + 1 < n && !(flag & i_bit) && !(flag & in_bit)) {
        res = MOD(res + solve(m_idx, n_idx + 2, flag | i_bit | in_bit));
    }

    memo[m_idx][n_idx][flag] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    cout << solve(0, 0, 0) << "\n";
}
