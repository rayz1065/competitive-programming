#include <bits/stdc++.h>
#define MAXN 250005

using namespace std;

int n_nodes;
vector<int> graph[MAXN];
int parent[MAXN];
bool path_broken[MAXN]; // whether the path to the parent is broken
int depth[MAXN];
int subtree_size[MAXN];
int lca_anc[20][MAXN];

int heavy_branch[MAXN];
vector<int> heavy_fenwick[MAXN];

void fw_add (int heavy_b, int i, int am) {
    for (i++; i < heavy_fenwick[heavy_b].size(); i += (i & (-i))) {
        heavy_fenwick[heavy_b][i] += am;
    }
}

int fw_sum (int heavy_b, int i) {
    int s = 0;
    for (i++; i > 0; i -= (i & (-i))) {
        s += heavy_fenwick[heavy_b][i];
    }
    return s;
}

int fw_range_sum (int heavy_b, int i, int j) {
    if (i == 0) {
        return fw_sum(heavy_b, j);
    }
    return fw_sum(heavy_b, j) - fw_sum(heavy_b, i - 1);
}

int hl_traverse (int a, int b) {
    // traverse from a to ancestor b, count broken paths
    int s = 0;
    while (a != b) {
        int from_depth = depth[a];
        int heavy_root = heavy_branch[a];
        int hb_depth = depth[heavy_root] - 1;
        int target = depth[heavy_root] > depth[b] ? parent[heavy_root] : b;
        int to_depth = depth[target];
        s += fw_range_sum(heavy_root, to_depth - hb_depth, from_depth - 1 - hb_depth);
        a = target;
    }
    return s;
}

int dfs (int node) {
    subtree_size[node] = 1;
    for (auto j: graph[node]) {
        if (parent[node] != j) {
            parent[j] = node;
            depth[j] = depth[node] + 1;
            subtree_size[node]+= dfs(j);
        }
    }
    return subtree_size[node] + 1;
}

void hl_decompose (int node) {
    for (auto j: graph[node]) {
        if (parent[node] != j) {
            int ch_heavy_b = subtree_size[j] >= subtree_size[node] / 2
                ? heavy_branch[node]
                : j;
            heavy_branch[j] = ch_heavy_b;
            hl_decompose(j);
        }
    }
}

void lca_build () {
    // add all the parents
    for (int i = 0; i < n_nodes; i++) {
        lca_anc[0][i] = parent[i];
    }
    for (int k = 1; k < 20; k++) {
        for (int i = 0; i < n_nodes; i++) {
            // size of the branch is 1 << k
            int anc = lca_anc[k - 1][i];
            if (anc == -1) {
                lca_anc[k][i] = -1;
                continue ;
            }
            lca_anc[k][i] = lca_anc[k - 1][anc];
        }
    }
}

void toggle_path (int x, int y) {
    // make y the parent
    if (parent[y] == x) {
        swap(x, y);
    }
    int am = path_broken[x] ? -1 : +1;
    path_broken[x] = !path_broken[x];
    int heavy_b = heavy_branch[x];
    fw_add(heavy_b, depth[x] - depth[heavy_b], am);
}

bool is_connected (int x, int y) {
    // make y the deepest node
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    // make the depths equal
    for (int k = 0; k < 20; k++) {
        if ((depth[y] - depth[x]) & (1 << k)) {
            if (hl_traverse(y, lca_anc[k][y])) {
                return false;
            }
            y = lca_anc[k][y];
        }
    }
    if (x == y) {
        return true;
    }
    for (int k = 19; k >= 0; k--) {
        if (lca_anc[k][x] != lca_anc[k][y]) {
            if (hl_traverse(x, lca_anc[k][x]) || hl_traverse(y, lca_anc[k][y])) {
                return false;
            }
            x = lca_anc[k][x], y = lca_anc[k][y];
        }
    }
    return !hl_traverse(x, lca_anc[0][x]) && !hl_traverse(y, lca_anc[0][y]);
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int q_queries;
    cin >> n_nodes >> q_queries;

    for (int i = 0; i < n_nodes - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    parent[0] = -1;
    dfs(0);
    hl_decompose(0);
    lca_build();

    for (int i = 0; i < n_nodes; i++) {
        heavy_fenwick[heavy_branch[i]].push_back(0);
        heavy_fenwick[i].push_back(0);
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