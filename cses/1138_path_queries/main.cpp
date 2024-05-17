#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int values[MAXN];
vector<int> graph[MAXN];

int subtree_size[MAXN];
int parent[MAXN];
int next_heavy_path_id, heavy_path_id[MAXN];
int heavy_path_depth[MAXN];
int heavy_path_length[MAXN], heavy_path_root[MAXN];

ll fenwick[MAXN];

void fenwick_add(int offset, int i, int n, int value) {
    for (i += 1; i <= n; i += i & (-i)) {
        fenwick[offset + i] += value;
    }
}

ll fenwick_sum(int offset, int i) {
    ll res = 0;

    for (i += 1; i > 0; i -= i & (-i)) {
        res += fenwick[offset + i];
    }

    return res;
}

void set_value(int node, int value) {
    int path_id = heavy_path_id[node];
    int depth = heavy_path_depth[node];
    int fenwick_n = heavy_path_length[path_id];
    fenwick_add(path_id, depth, fenwick_n, value - values[node]);
    values[node] = value;
}

void fenwick_init() {
    for (int i = 0; i < n; i++) {
        int value = values[i];
        values[i] = 0;
        set_value(i, value);
    }
}

ll sum_to_root(int node) {
    ll res = 0;

    while (node != -1) {
        int path_id = heavy_path_id[node];
        int depth = heavy_path_depth[node];

        res += fenwick_sum(path_id, depth);
        node = parent[heavy_path_root[path_id]];
    }

    return res;
}

void dfs(int node) {
    subtree_size[node] = 1;

    for (auto j : graph[node]) {
        if (j != parent[node]) {
            parent[j] = node;
            dfs(j);
            subtree_size[node] += subtree_size[j];
        }
    }
}

void heavy_paths_dfs(int node) {
    int heaviest_child = -1;
    for (auto j : graph[node]) {
        if (parent[node] != j &&
            (heaviest_child == -1 ||
             subtree_size[j] > subtree_size[heaviest_child])) {
            heaviest_child = j;
        }
    }

    if (heaviest_child != -1) {
        heavy_path_id[heaviest_child] = heavy_path_id[node];
        heavy_path_depth[heaviest_child] = heavy_path_depth[node] + 1;
        heavy_paths_dfs(heaviest_child);
    } else {
        heavy_path_length[heavy_path_id[node]] += heavy_path_depth[node] + 1;
        next_heavy_path_id += heavy_path_length[heavy_path_id[node]];
    }

    for (auto j : graph[node]) {
        if (j != parent[node] && j != heaviest_child) {
            heavy_path_id[j] = next_heavy_path_id;
            heavy_path_root[next_heavy_path_id] = j;
            heavy_paths_dfs(j);
        }
    }
}

void find_heavy_paths() {
    parent[0] = -1;
    dfs(0);
    heavy_path_id[0] = 0;
    heavy_paths_dfs(0);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    find_heavy_paths();
    fenwick_init();

    while (q--) {
        int q_type, node;
        cin >> q_type >> node;
        node--;

        if (q_type == 1) {
            int value;
            cin >> value;
            set_value(node, value);
        } else {
            cout << sum_to_root(node) << "\n";
        }
    }
}
