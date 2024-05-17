#include <bits/stdc++.h>
#define MAXN 200005
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)
#define ST_SIZE (1 << 18)

using namespace std;

int n;
int values[MAXN];
vector<int> graph[MAXN];

int depth[MAXN];
int subtree_size[MAXN];
int parent[MAXN];
int next_heavy_path_id, heavy_path_id[MAXN];
int heavy_path_depth[MAXN];
int heavy_path_length[MAXN], heavy_path_root[MAXN];

int segment_tree[ST_SIZE << 1];

void st_set(int i, int value) {
    i += ST_SIZE;
    segment_tree[i] = value;
    for (i >>= 1; i; i >>= 1) {
        segment_tree[i] =
            max(segment_tree[ST_LEFT(i)], segment_tree[ST_RIGHT(i)]);
    }
}

void set_value(int node, int value) {
    int path_id = heavy_path_id[node];
    int depth = heavy_path_depth[node];
    st_set(path_id + depth, value);
    values[node] = value;
}

void st_init() {
    for (int i = 0; i < n; i++) {
        set_value(i, values[i]);
    }
}

int st_max(int left, int right) {
    int res = INT_MIN >> 1;

    for (left += ST_SIZE, right += ST_SIZE + 1; left < right;
         left >>= 1, right >>= 1) {
        if (left & 1) {
            res = max(res, segment_tree[left++]);
        }
        if (right & 1) {
            res = max(res, segment_tree[--right]);
        }
    }

    return res;
}

int max_in_path(int a, int b) {
    int res = INT_MIN >> 1;

    if (depth[heavy_path_root[a]] > depth[heavy_path_root[b]]) {
        swap(a, b);
    }

    while ((depth[heavy_path_root[b]] > depth[heavy_path_root[a]])) {
        int path_id = heavy_path_id[b];
        int path_depth = heavy_path_depth[b];
        res = max(res, st_max(path_id, path_id + path_depth));
        b = parent[heavy_path_root[b]];
    }

    while (heavy_path_root[b] != heavy_path_root[a]) {
        if ((depth[heavy_path_root[b]] >= depth[heavy_path_root[a]])) {
            int path_id = heavy_path_id[b];
            int path_depth = heavy_path_depth[b];
            res = max(res, st_max(path_id, path_id + path_depth));
            b = parent[heavy_path_root[b]];
        } else {
            int path_id = heavy_path_id[a];
            int path_depth = heavy_path_depth[a];
            res = max(res, st_max(path_id, path_id + path_depth));
            a = parent[heavy_path_root[a]];
        }
    }

    int path_id = heavy_path_id[a];
    int lo = min(heavy_path_depth[a], heavy_path_depth[b]);
    int hi = max(heavy_path_depth[a], heavy_path_depth[b]);

    return max(res, st_max(path_id + lo, path_id + hi));
}

void dfs(int node) {
    subtree_size[node] = 1;

    for (auto j : graph[node]) {
        if (j != parent[node]) {
            depth[j] = depth[node] + 1;
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
        heavy_path_root[heaviest_child] = heavy_path_root[node];
        heavy_paths_dfs(heaviest_child);
    } else {
        next_heavy_path_id += heavy_path_depth[node] + 1;
    }

    for (auto j : graph[node]) {
        if (j != parent[node] && j != heaviest_child) {
            heavy_path_id[j] = next_heavy_path_id;
            heavy_path_root[j] = j;
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
    st_init();

    while (q--) {
        int q_type, node;
        cin >> q_type >> node;
        node--;

        if (q_type == 1) {
            int value;
            cin >> value;
            set_value(node, value);
        } else {
            int other;
            cin >> other;
            other--;
            cout << max_in_path(node, other) << " ";
        }
    }

    cout << "\n";
}
