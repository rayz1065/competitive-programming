#include <bits/stdc++.h>
#define MAXN 1005
#define MOV 4

using namespace std;

typedef pair<int, int> pii;

int n, m;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int parent_dire[MAXN][MAXN];
int mov_r[] = {-1, 0, 1, 0}, mov_c[] = {0, -1, 0, 1};
char mov_name[] = {'U', 'L', 'D', 'R'};

pii find_coords(char needle) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == needle) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool in_range(int r, int c) { return r >= 0 && c >= 0 && r < n && c < m; }

int solve(pii source, pii sink) {
    queue<pii> ff;
    ff.push(source);
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + m, INT_MAX >> 1);
    }
    dist[source.first][source.second] = 0;

    while (!ff.empty()) {
        pii curr = ff.front();
        ff.pop();
        for (int i = 0; i < MOV; i++) {
            int new_r = curr.first + mov_r[i], new_c = curr.second + mov_c[i];
            if (in_range(new_r, new_c) &&
                dist[new_r][new_c] == (INT_MAX >> 1) &&
                grid[new_r][new_c] == '.') {
                dist[new_r][new_c] = dist[curr.first][curr.second] + 1;
                parent_dire[new_r][new_c] = i;
                ff.push({new_r, new_c});
            }
        }
    }

    return dist[sink.first][sink.second];
}

vector<char> find_path(pii sink) {
    vector<char> res;

    pii curr = sink;
    while (dist[curr.first][curr.second] != 0) {
        int i = parent_dire[curr.first][curr.second];
        res.push_back(mov_name[i]);
        i = (i + 2) % MOV;
        curr = {curr.first + mov_r[i], curr.second + mov_c[i]};
    }

    reverse(res.begin(), res.end());

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    pii source = find_coords('A');
    pii sink = find_coords('B');
    grid[source.first][source.second] = '.';
    grid[sink.first][sink.second] = '.';

    int res = solve(source, sink);
    if (res == INT_MAX >> 1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n" << res << "\n";
    auto path = find_path(sink);

    for (auto i : path) {
        cout << i;
    }
    cout << "\n";
}
