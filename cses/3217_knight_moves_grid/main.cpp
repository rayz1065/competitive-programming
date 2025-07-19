#include <bits/stdc++.h>
#define MAXN 1005
#define INF (INT_MAX >> 1)

using namespace std;

int n;
vector<pair<int, int>> mov;
int dist[MAXN][MAXN];

bool in_range(int r, int c) { return r >= 0 && c >= 0 && r < n && c < n; }

void bfs() {
    queue<pair<int, int>> ff;
    ff.push({0, 0});

    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + n, INF);
    }
    dist[0][0] = 0;

    while (!ff.empty()) {
        auto curr = ff.front();
        ff.pop();
        int r = curr.first, c = curr.second;
        int curr_d = dist[r][c];

        for (auto deltas : mov) {
            int dr = deltas.first, dc = deltas.second;
            int new_r = r + dr, new_c = c + dc;
            if (in_range(new_r, new_c) && dist[new_r][new_c] == INF) {
                dist[new_r][new_c] = curr_d + 1;
                ff.push({new_r, new_c});
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if (abs(i) + abs(j) == 3) {
                mov.push_back({i, j});
            }
        }
    }

    cin >> n;

    bfs();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << " \n"[j + 1 == n];
        }
    }
}
