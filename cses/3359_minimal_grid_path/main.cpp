#include <bits/stdc++.h>
#define MAXN 3005

using namespace std;

int mov_r[] = {1, 0}, mov_c[] = {0, 1};
int n;
char grid[MAXN][MAXN];
bool visited[MAXN][MAXN];

bool in_range(int r, int c) { return 0 <= r && r < n && 0 <= c && c < n; }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    visited[0][0] = true;

    string solution;
    solution.push_back(grid[0][0]);

    for (int steps = 1; steps < 2 * n - 1; steps++) {
        char best = 'Z' + 1;
        vector<pair<int, int>> next;

        for (int i = 0; i < n; i++) {
            int r = steps - i, c = i;
            if (r < 0 || r >= n) {
                continue;
            }

            bool visitable = false;
            for (int j = 0; j < 2 && !visitable; j++) {
                int prev_r = r - mov_r[j], prev_c = c - mov_c[j];
                visitable = in_range(prev_r, prev_c) && visited[prev_r][prev_c];
            }

            if (visitable && grid[r][c] == best) {
                next.push_back({r, c});
            } else if (visitable && grid[r][c] < best) {
                next.clear();
                next.push_back({r, c});
                best = grid[r][c];
            }
        }

        for (auto i : next) {
            visited[i.first][i.second] = true;
        }

        solution.push_back(best);
    }

    cout << solution << "\n";
}
