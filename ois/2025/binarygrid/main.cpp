#include <bits/stdc++.h>
#define MAXN 2005
#define UNSOLVABLE (INT_MAX >> 1)

using namespace std;

int n, m;
bool grid[MAXN][MAXN], tmp[MAXN][MAXN];
int memo[MAXN][2][2];

void transpose() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tmp[j][i] = grid[i][j];
        }
    }

    swap(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = tmp[i][j];
        }
    }
}

int solve_rows(int j, bool swap_b1, bool swap_b2) {
    if (memo[j][swap_b1][swap_b2] != 0) {
        return memo[j][swap_b1][swap_b2] - 1;
    } else if (j == m) {
        return 0;
    }

    int res = UNSOLVABLE;

    bool req_swap = false, req_no_swap = false;
    if (j >= 2) {
        for (int i = 0; i < n; i++) {
            bool b2 = grid[i][j - 2] ^ swap_b2;
            bool b1 = grid[i][j - 1] ^ swap_b1;
            bool b0 = grid[i][j];

            if (b1 == b2 && b2 == b0) {
                req_swap = true;
            } else if (b1 == b2) {
                req_no_swap = true;
            }
        }
    }

    if (!req_swap) {
        res = min(res, solve_rows(j + 1, 0, swap_b1));
    }

    if (!req_no_swap) {
        res = min(res, solve_rows(j + 1, 1, swap_b1) + 1);
    }

    memo[j][swap_b1][swap_b2] = res + 1;
    return res;
}

int solve() {
    int res = 0;

    memset(memo, 0, sizeof memo);
    res = solve_rows(0, 0, 0);
    if (res == UNSOLVABLE) {
        return -1;
    }

    transpose();

    memset(memo, 0, sizeof memo);
    res += solve_rows(0, 0, 0);

    return res >= UNSOLVABLE ? -1 : res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            string row;
            cin >> row;
            for (int j = 0; j < m; j++) {
                cerr.flush();
                grid[i][j] = row[j] - '0';
            }
        }

        cout << solve() << "\n";
    }
}
