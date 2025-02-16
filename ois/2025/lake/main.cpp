#include <bits/stdc++.h>
#define MAXN 1005
#define MOV 4

using namespace std;

int n, m;
char grid[MAXN][MAXN];
int mov_r[] = {-1, 0, 1, 0}, mov_c[] = {0, -1, 0, 1};

bool in_range(int r, int c) { return 0 <= r && r < n && 0 <= c && c < m; }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int res = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            for (int mov = 0; mov < MOV; mov++) {
                int new_r = r + mov_r[mov], new_c = c + mov_c[mov];
                res += grid[r][c] == '.' && in_range(new_r, new_c) &&
                       grid[new_r][new_c] == '#';
            }
        }
    }

    cout << res << "\n";
}
