#include <bits/stdc++.h>
#define MAXN 1005
#define MOV 4
#define INF (INT_MAX >> 1)

using namespace std;

int n, m;
char grid[MAXN][MAXN];
int monster_dist[MAXN][MAXN];
int dist[MAXN][MAXN];
int parent_mov[MAXN][MAXN];
int mov_r[] = {-1, 0, 1, 0};
int mov_c[] = {0, -1, 0, 1};
char mov_name[] = {'U', 'L', 'D', 'R'};

bool in_range(int r, int c) { return 0 <= r && r < n && 0 <= c && c < m; }
char get_cell(int r, int c) {
    if (in_range(r, c)) {
        return grid[r][c];
    }
    return '#';
}
bool is_border(int r, int c) {
    return r == 0 || r == n - 1 || c == 0 || c == m - 1;
}

void bfs(vector<pair<int, int>> start, int dist[][MAXN], bool player) {
    queue<pair<int, int>> ff;
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + m, INF);
    }
    for (auto i : start) {
        ff.push({i.first, i.second});
        dist[i.first][i.second] = 0;
    }

    while (!ff.empty()) {
        int r, c;
        tie(r, c) = ff.front();
        ff.pop();
        for (int i = 0; i < MOV; i++) {
            int new_r = r + mov_r[i], new_c = c + mov_c[i];
            if (get_cell(new_r, new_c) == '.' && dist[new_r][new_c] == INF &&
                !(player && monster_dist[new_r][new_c] <= dist[r][c] + 1)) {
                ff.push({new_r, new_c});
                dist[new_r][new_c] = dist[r][c] + 1;
                parent_mov[new_r][new_c] = i;
            }
        }
    }
}

pair<int, int> solve() {
    vector<pair<int, int>> monsters;
    pair<int, int> start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                start = {i, j};
                grid[i][j] = '.';
            } else if (grid[i][j] == 'M') {
                monsters.push_back({i, j});
                grid[i][j] = '.';
            }
        }
    }

    bfs(monsters, monster_dist, false);
    bfs({start}, dist, true);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (is_border(i, j) && dist[i][j] != INF) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    auto res = solve();
    if (res.first == -1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    cout << dist[res.first][res.second] << "\n";

    int r = res.first, c = res.second;
    vector<char> moves;
    while (dist[r][c] > 0) {
        int i = parent_mov[r][c];
        moves.push_back(mov_name[i]);
        r = r - mov_r[i], c = c - mov_c[i];
    }
    reverse(moves.begin(), moves.end());
    for (auto i : moves) {
        cout << i;
    }
    cout << "\n";
}
