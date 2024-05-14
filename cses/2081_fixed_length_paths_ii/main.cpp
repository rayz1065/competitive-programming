#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, k1, k2;
int fenwick[MAXN];
vector<int> graph[MAXN];

int subtree_size[MAXN];
int subtree_cached_parent[MAXN];
bool centroid_used[MAXN];

void fenwick_add(int i, int value) {
    for (i += 1; i < MAXN; i += i & (-i)) {
        fenwick[i] += value;
    }
}

ll fenwick_sum(int i) {
    ll res = 0;

    for (i += 1; i > 0; i -= i & (-i)) {
        res += fenwick[i];
    }

    return res;
}

ll fenwick_range_sum(int i, int j) {
    return fenwick_sum(j) - (i == 0 ? 0 : fenwick_sum(i - 1));
}

int get_subtree_size(int node, int parent) {
    if (subtree_cached_parent[node] == parent + 1) {
        return subtree_size[node];
    }
    subtree_cached_parent[node] = parent + 1;

    subtree_size[node] = 1;

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            subtree_size[node] += get_subtree_size(j, node);
        }
    }

    return subtree_size[node];
}

int get_centroid(int node, int parent, int tree_size) {
    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j] &&
            subtree_size[j] > tree_size / 2) {
            return get_centroid(j, node, tree_size);
        }
    }

    return node;
}

void dfs_add(int node, int parent, int depth, bool small_tree_flag, int value) {
    if (depth > k2 || (small_tree_flag && depth > k1 - 1)) {
        return;
    }

    fenwick_add(depth, value);

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            dfs_add(j, node, depth + 1, small_tree_flag, value);
        }
    }
}

ll dfs_sum(int node, int parent, int depth, bool small_tree_flag) {
    if (depth > k2 || (small_tree_flag && depth > k1 - 1)) {
        return 0;
    }

    int min_depth = small_tree_flag ? 0 : max(0, k1 - depth);
    int max_depth = small_tree_flag ? k1 - 1 - depth : k2 - depth;
    ll res = fenwick_range_sum(min_depth, max_depth);

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            res += dfs_sum(j, node, depth + 1, small_tree_flag);
        }
    }

    return res;
}

ll get_total_combinations(int node) {
    get_subtree_size(node, node);
    vector<int> sizes(1, 1);
    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            sizes.push_back(subtree_size[j]);
        }
    }

    ll res = 0;

    for (int i = 0; i < (int)sizes.size(); i++) {
        for (int j = i + 1; j < (int)sizes.size(); j++) {
            res += (ll)sizes[i] * sizes[j];
        }
    }

    return res;
}

ll get_paths_count(int node, int tree_size) {
    bool small_tree_flag = (tree_size < k2);

    dfs_add(node, node, 0, small_tree_flag, 1);
    fenwick_add(0, 1);  // double count the root

    ll res = 0;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            dfs_add(j, node, 1, small_tree_flag, -1);

            res += dfs_sum(j, node, 1, small_tree_flag);

            dfs_add(j, node, 1, small_tree_flag, 1);
        }
    }

    fenwick_add(0, -1);
    dfs_add(node, node, 0, small_tree_flag, -1);

    res /= 2;

    if (small_tree_flag) {
        res = get_total_combinations(node) - res;
    }

    return res;
}

ll centroid_decomposition(int node) {
    int tree_size = get_subtree_size(node, node);
    if (tree_size < k1) {
        return 0;
    }

    node = get_centroid(node, node, tree_size);

    ll res = get_paths_count(node, tree_size);

    centroid_used[node] = true;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            res += centroid_decomposition(j);
        }
    }

    return res;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k1 >> k2;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cout << centroid_decomposition(0) << "\n";
}
