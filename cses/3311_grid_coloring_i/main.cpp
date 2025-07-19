#include <bits/stdc++.h>
#define MAXN 505
#define COLORS 4

using namespace std;

int n, m;
char grid[MAXN][MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool used[COLORS] = {0};
            used[grid[i][j] - 'A'] = true;
            if (i > 0) {
                used[grid[i - 1][j] - 'A'] = true;
            }
            if (j > 0) {
                used[grid[i][j - 1] - 'A'] = true;
            }

            char found = 0;
            for (int k = 0; k < COLORS && !found; k++) {
                if (!used[k]) {
                    found = k + 'A';
                }
            }

            grid[i][j] = found;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i] << "\n";
    }
}
