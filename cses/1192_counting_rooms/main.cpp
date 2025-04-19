#include <bits/stdc++.h>
#define MAXN 1005
#define MOV 4

using namespace std;

int n, m;
char grid[MAXN][MAXN];
bool visited[MAXN][MAXN];
int mov_r[] = {-1, 0, 1, 0}, mov_c[] = {0, 1, 0, -1};

bool in_range(int r, int c) { return r >= 0 && c >= 0 && r < n && c < m; }

void dfs(int r, int c) {
    visited[r][c] = true;
    for (int i = 0; i < MOV; i++) {
        int new_r = r + mov_r[i], new_c = c + mov_c[i];
        if (in_range(new_r, new_c) && grid[new_r][new_c] == '.' &&
            !visited[new_r][new_c]) {
            dfs(new_r, new_c);
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                res += 1;
            }
        }
    }

    cout << res << "\n";
}
