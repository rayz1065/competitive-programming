#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1005

using namespace std;

typedef long long ll;

int n, m;
int grid[MAXN][MAXN];
ll pref_sums[MAXN][MAXN];

ll sum (int i, int l, int r) {
    if (l == 0) return pref_sums[i][r];
    return pref_sums[i][r] - pref_sums[i][l - 1];
}

ll calc_sum (int r, int c) {
    int row_dist = min(r, n - 1 - r);
    int col_dist = min(c, m - 1 - c);
    int dist = min(row_dist, col_dist);
    ll s = 0;
    for (int i = r - dist; i <= r + dist; i++) {
        int il = c - (dist - abs(i - r)), ir = c + (dist - abs(i - r));
        s += sum(i, il, ir);
    }
    return s;
}

pair<int, int> best_dist () {
    ll s = 0;
    int best_r, best_c;
    // vertical lines
    for (int i = 0; i < n; i++) {
        for (int j = (m - 1) / 2; j <= m / 2; j++) {
            ll curr = calc_sum(i, j);
            if (curr > s) s = curr, best_r = i, best_c = j;
        }
    }
    // horizzontal lines
    for (int i = (n - 1) / 2; i <= n / 2; i++) {
        for (int j = 0; j < m; j++) {
            ll curr = calc_sum(i, j);
            if (curr > s) s = curr, best_r = i, best_c = j;
        }
    }
    // diagonal lines
    for (int i = 0, j = 0; i < n && j < m; i++, j++) {
        ll curr = calc_sum(i, j);
        if (curr > s) s = curr, best_r = i, best_c = j;
    }
    for (int i = n - 1, j = 0; i >= 0 && j < m; i--, j++) {
        ll curr = calc_sum(i, j);
        if (curr > s) s = curr, best_r = i, best_c = j;
    }
    for (int i = 0, j = m - 1; i < n && j >= 0; i++, j--) {
        ll curr = calc_sum(i, j);
        if (curr > s) s = curr, best_r = i, best_c = j;
    }
    for (int i = n - 1, j = m - 1; i >= 0 && j >= 0; i--, j--) {
        ll curr = calc_sum(i, j);
        if (curr > s) s = curr, best_r = i, best_c = j;
    }

    return { best_r, best_c };
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        ll t = 0;
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            pref_sums[i][j] = t + grid[i][j];
            t = pref_sums[i][j];
        }
    }
    auto res = best_dist();
    cout << res.first << " " << res.second << "\n";
}
