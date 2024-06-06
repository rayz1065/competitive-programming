#include <bits/stdc++.h>
#define MAXN 100005
#define ST_SIZE (1 << 17)
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)

using namespace std;

int n;
int values[MAXN];
int parent[MAXN], depth[MAXN], subtree_size[MAXN];
vector<int> graph[MAXN];

// heavy light decomposition
int next_hl_index, hl_index[MAXN], heavy_path_root[MAXN];

// segment tree
int segment_tree[ST_SIZE << 1];

void hl_decompose(int node) {
    hl_index[node] = next_hl_index++;

    int heaviest_child = -1, heaviest_weight = -1;
    for (auto j : graph[node]) {
        if (j != parent[node] && subtree_size[j] > heaviest_weight) {
            heaviest_child = j;
            heaviest_weight = subtree_size[j];
        }
    }

    if (heaviest_child != -1) {
        heavy_path_root[heaviest_child] = heavy_path_root[node];
        hl_decompose(heaviest_child);
    }

    for (auto j : graph[node]) {
        if (j != parent[node] && j != heaviest_child) {
            heavy_path_root[j] = j;
            hl_decompose(j);
        }
    }
}

void dfs(int node) {
    subtree_size[node] = 1;

    for (auto j : graph[node]) {
        if (j != parent[node]) {
            parent[j] = node;
            depth[j] = depth[node] + 1;
            dfs(j);
            subtree_size[node] += subtree_size[j];
        }
    }
}

int segment_tree_xor(int l, int r) {
    int res = 0;

    for (l += ST_SIZE, r += ST_SIZE + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res ^= segment_tree[l++];
        }
        if (r & 1) {
            res ^= segment_tree[--r];
        }
    }

    return res;
}

void segment_tree_set(int i, int value) {
    i += ST_SIZE;
    segment_tree[i] = value;
    for (i >>= 1; i; i >>= 1) {
        segment_tree[i] = segment_tree[ST_LEFT(i)] ^ segment_tree[ST_RIGHT(i)];
    }
}

void st_init() {
    for (int i = 0; i < n; i++) {
        segment_tree[hl_index[i] + ST_SIZE] = values[i];
    }

    for (int i = ST_SIZE - 1; i; i--) {
        segment_tree[i] = segment_tree[ST_LEFT(i)] ^ segment_tree[ST_RIGHT(i)];
    }
}

void update_value(int node, int value) {
    values[node] = value;
    segment_tree_set(hl_index[node], value);
}

int get_enjoyment(int a, int b) {
    int res = 0;

    while (heavy_path_root[a] != heavy_path_root[b]) {
        if (depth[heavy_path_root[a]] > depth[heavy_path_root[b]]) {
            swap(a, b);
        }

        res ^= segment_tree_xor(hl_index[heavy_path_root[b]], hl_index[b]);
        b = parent[heavy_path_root[b]];
    }

    if (depth[a] > depth[b]) {
        swap(a, b);
    }

    res ^= segment_tree_xor(hl_index[a], hl_index[b]);

    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("cowland.in", ios::in);
    cout.open("cowland.out", ios::out);
#endif
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

    dfs(0);
    hl_decompose(0);
    st_init();

    while (q--) {
        int query_type, a, b;
        cin >> query_type >> a >> b;

        if (query_type == 1) {
            a--;
            update_value(a, b);
        } else {
            a--, b--;
            cout << get_enjoyment(a, b) << "\n";
        }
    }
}
