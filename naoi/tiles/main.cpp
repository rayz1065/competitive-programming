#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 100005

using namespace std;

int n;
char grid[2][MAXN];
int memo[MAXN][16];

inline int mod(int x) { return x % MOD; }

int solve(int i, int flag) {
    if (memo[i][flag]) {
        return memo[i][flag] - 1;
    } else if (i >= n) {
        return 1;
    }

    bool curr[2][3] = {
        {
            (flag & (1 << 0)) || grid[0][i - 1] == '#',
            (flag & (1 << 2)) || grid[0][i] == '#',
            grid[0][i + 1] == '#',
        },
        {
            (flag & (1 << 1)) || grid[1][i - 1] == '#',
            (flag & (1 << 3)) || grid[1][i] == '#',
            grid[1][i + 1] == '#',
        },
    };

    int res = 0;

    bool can_h_above = !curr[0][1] && !curr[0][2];
    bool can_h_below = !curr[1][1] && !curr[1][2];
    bool can_v = !curr[0][1] && !curr[1][1];
    bool must_fill_above = !curr[0][0] && !curr[0][1];
    bool must_fill_below = !curr[1][0] && !curr[1][1];

    // =
    if (can_h_above && can_h_below) {
        res = mod(res + solve(i + 2, 3));
    }

    // -
    if (can_h_above && !must_fill_below) {
        res = mod(res + solve(i + 1, (1 << 0) | (1 << 2) | (flag >> 2)));
    };

    // _
    if (can_h_below && !must_fill_above) {
        res = mod(res + solve(i + 1, (1 << 1) | (1 << 3) | (flag >> 2)));
    };

    // |
    if (can_v) {
        res = mod(res + solve(i + 1, (1 << 0) | (1 << 1) | (flag >> 2)));
    }

    //
    if (!must_fill_above && !must_fill_below && !can_v) {
        res = mod(res + solve(i + 1, flag >> 2));
    }

    memo[i][flag] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> m >> n;
    for (int i = 0; i < 2; i++) {
        fill(grid[i], grid[i] + n + 5, '#');
        grid[i][n + 5] = 0;
        if (i < m) {
            cin >> grid[i];
            grid[i][n] = '#';
        }
    }

    cout << solve(0, 3) << "\n";
}
