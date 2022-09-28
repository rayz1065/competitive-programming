#include <bits/stdc++.h>
#define MAXN 2505

using namespace std;

int n_nodes;
vector<int> graph[MAXN];
bool adj_mat[MAXN][MAXN];
bool visited[MAXN];

void dfs (int node) {
    if (visited[node]) {
        return ;
    }
    visited[node] = true;
    for (auto j: graph[node]) {
        if (adj_mat[node][j]) {
            dfs(j);
        }
    }
}

void toggle_path (int x, int y) {
    adj_mat[x][y] = !adj_mat[x][y];
    adj_mat[y][x] = !adj_mat[y][x];
}

bool is_connected (int x, int y) {
    fill(visited, visited + n_nodes, false);
    dfs(x);
    return visited[y];
}

int main () {
    int q_queries;
    cin >> n_nodes >> q_queries;

    for (int i = 0; i < n_nodes - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        adj_mat[a][b] = true;
        adj_mat[b][a] = true;
    }

    int outfit_sum = 0;
    while (q_queries--) {
        int q_type, x, y;
        cin >> q_type >> x >> y;
        if (q_type == 1) {
            x--, y--; // add/remove branch
            toggle_path(x, y);
        } else {
            // check if reachable, update outfit sum
            x = (x + outfit_sum) % n_nodes;
            y = (y + outfit_sum) % n_nodes;
            int outfit = is_connected(x, y);
            outfit_sum += outfit;
            cout << outfit << "\n";
        }
    }
}
