#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;

struct Branch {
    int to;
    int weight;
};

vector<Branch> graph[MAXN];
unordered_set<int> interesting_nodes;
bool is_interesting[MAXN];
bool visited[MAXN];
pair<int, int> parent[MAXN];
int depth[MAXN];

void remove_interesting (int node) {
    interesting_nodes.erase(node);
}

void add_interesting (int node) {
    interesting_nodes.insert(node);
}

int calc_diff (int i, int j) {
    if (depth[i] < depth[j]) swap(i, j);
    int s = 0;
    while (depth[i] > depth[j]) {
        s ^= parent[i].second;
        i = parent[i].first;
    }
    while (i != j) {
        s ^= parent[i].second ^ parent[j].second;
        i = parent[i].first, j = parent[j].first;
    }
    return s;
}

int find_best () {
    int best_diff = 0;
    for (auto i: interesting_nodes) {
        for (auto j: interesting_nodes) {
            if (i <= j) continue ;
            best_diff = max(best_diff, calc_diff(i, j));
        }
    }
    return best_diff;
}

void dfs (int node) {
    visited[node] = true;
    for (auto b: graph[node]) {
        if (!visited[b.to]) {
            parent[b.to] = { node, b.weight };
            depth[b.to] = depth[node] + 1;
            dfs(b.to);
        }
    }
}

int main () {
    int n, q_queries;
    cin >> n >> q_queries;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
    }

    dfs(0);

    for (int i = 0; i < q_queries; i++) {
        int node;
        cin >> node;
        node--;
        if (is_interesting[node]) {
            remove_interesting(node);
        } else {
            add_interesting(node);
        }
        is_interesting[node] = !is_interesting[node];
        cout << find_best() << "\n";
    }
}
