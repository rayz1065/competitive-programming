#include <bits/stdc++.h>
#define MAXN 505

using namespace std;

int n, m;
int grid[MAXN][MAXN];
int ops[MAXN][MAXN][2];

void update(int r, int c, int dr, int dc, int v) {
    ops[r][c][dr] += v;
    for (int dist = 0; dist < 3; dist++) {
        int new_r = r + dr * dist, new_c = c + dc * dist;
        grid[new_r][new_c] += v;
    }
}

bool all_zeros() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin(), m = fastin();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = fastin();
        }
    }

    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < m; j++) {
            update(i, j, 1, 0, -grid[i][j]);
        }
    }

    for (int i = n - 2; i < n; i++) {
        for (int j = 0; j < m - 2; j++) {
            update(i, j, 0, 1, -grid[i][j]);
        }
    }

    if (!all_zeros()) {
        cout << "NO\n";
        return 0;
    }

    vector<pair<int, tuple<int, int, int, int>>> changes;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (ops[r][c][0] != 0) {
                changes.push_back({ops[r][c][0], {r, c, r, c + 2}});
            }
            if (ops[r][c][1] != 0) {
                changes.push_back({ops[r][c][1], {r, c, r + 2, c}});
            }
        }
    }

    cout << "YES\n";
    cout << changes.size() << "\n";
    for (auto change : changes) {
        if (change.first > 0) {
            int r, c, new_r, new_c;
            tie(r, c, new_r, new_c) = change.second;
            cout << r + 1 << " " << c + 1 << " " << new_r + 1 << " "
                 << new_c + 1 << " " << change.first << "\n";
        }
    }
    for (auto change : changes) {
        if (change.first < 0) {
            int r, c, new_r, new_c;
            tie(r, c, new_r, new_c) = change.second;
            cout << r + 1 << " " << c + 1 << " " << new_r + 1 << " "
                 << new_c + 1 << " " << change.first << "\n";
        }
    }
}
