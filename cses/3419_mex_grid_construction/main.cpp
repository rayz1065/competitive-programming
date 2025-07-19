#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int grid[MAXN][MAXN];

int get_value(int r, int c) {
    unordered_set<int> found;
    for (int i = 0; i < r; i++) {
        found.insert(grid[i][c]);
    }
    for (int i = 0; i < c; i++) {
        found.insert(grid[r][i]);
    }

    for (int i = 0; i < r + c + 5; i++) {
        if (found.find(i) == found.end()) {
            return i;
        }
    }
    assert(false);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = get_value(i, j);
            cout << grid[i][j] << "\t\n"[j + 1 == n];
        }
    }
}
