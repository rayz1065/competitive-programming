#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
vector<int> graph[MAXN];
int parent[MAXN];
int dist[MAXN];

int bfs(int u, int v) {
    queue<int> ff;
    ff.push(u);
    fill(dist, dist + n, INT_MAX >> 1);
    dist[u] = 0;

    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();

        for (auto i : graph[node]) {
            if (dist[i] == INT_MAX >> 1) {
                dist[i] = dist[node] + 1;
                ff.push(i);
                parent[i] = node;
            }
        }
    }

    return dist[v];
}

vector<int> find_path(int target) {
    int node = target;
    vector<int> res;

    res.push_back(node);
    while (dist[node] > 0) {
        node = parent[node];
        res.push_back(node);
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int res = bfs(0, n - 1);
    if (res == INT_MAX >> 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path = find_path(n - 1);
    cout << res + 1 << "\n";
    for (auto i : path) {
        cout << i + 1 << " ";
    }
    cout << "\n";
}
