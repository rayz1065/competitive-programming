#include <bits/stdc++.h>
#define MAXN 300005
#define LOGMAXN 20

using namespace std;

int n;
vector<int> graph[MAXN];
bool shop[MAXN];
pair<int, int> customers[MAXN];  // favorite, patience

int customer_max_distance[MAXN];
int solutions[MAXN];

// lca
int lca_up[MAXN][LOGMAXN];
int depth[MAXN];

// centroid
int centroid_root;
bool centroid_used[MAXN];
int cached_subtree_size[MAXN];
int subtree_size[MAXN];
vector<pair<int, int>> centroid_ancestors[MAXN];
int nearest_shop_distance[MAXN];
vector<int> centroid_graph[MAXN];

// fenwick tree
int accepted_depths[MAXN];  // how many nodes accept a certain depth

// lca

void lca_dfs(int node) {
    for (auto j : graph[node]) {
        if (j != lca_up[node][0]) {
            lca_up[j][0] = node;
            depth[j] = depth[node] + 1;
            lca_dfs(j);
        }
    }
}

void build_lca() {
    lca_up[0][0] = -1;
    lca_dfs(0);

    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 0; i < n; i++) {
            int up = lca_up[i][j - 1];
            lca_up[i][j] = up == -1 ? -1 : lca_up[up][j - 1];
        }
    }
}

int lca_get_distance(int a, int b) {
    int res = 0;
    if (depth[a] > depth[b]) {
        swap(a, b);
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int distance = (1 << j);
        int new_depth = depth[b] - distance;
        if (new_depth >= depth[a]) {
            b = lca_up[b][j];
            res += distance;
        }
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        if (lca_up[a][j] != lca_up[b][j]) {
            int distance = (1 << j);
            res += 2 * distance;
            a = lca_up[a][j];
            b = lca_up[b][j];
        }
    }

    if (a != b) {
        res += 2;
    }

    return res;
}

// centroid decomposition

int get_subtree_size(int node, int parent) {
    if (cached_subtree_size[node] == parent + 1) {
        return subtree_size[node];
    }
    cached_subtree_size[node] = parent + 1;
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

void centroid_build_ancestors(int node, int parent, int centroid,
                              int distance) {
    centroid_ancestors[node].push_back({centroid, distance});

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            centroid_build_ancestors(j, node, centroid, distance + 1);
        }
    }
}

int centroid_decomposition(int node) {
    int tree_size = get_subtree_size(node, node);
    node = get_centroid(node, node, tree_size);

    centroid_build_ancestors(node, node, node, 0);

    centroid_used[node] = true;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            int child = centroid_decomposition(j);
            centroid_graph[node].push_back(child);
        }
    }

    return node;
}

void _centroid_add_shop(int node) {
    for (auto [other, distance] : centroid_ancestors[node]) {
        nearest_shop_distance[other] =
            min(nearest_shop_distance[other], distance);
    }
}

void centroid_add_shops() {
    fill(nearest_shop_distance, nearest_shop_distance + n, INT_MAX >> 1);

    for (int i = 0; i < n; i++) {
        if (shop[i]) {
            _centroid_add_shop(i);
        }
    }
}

int get_nearest_shop_distance(int node) {
    int res = INT_MAX >> 1;

    for (auto [other, distance] : centroid_ancestors[node]) {
        res = min(res, distance + nearest_shop_distance[other]);
    }

    return res;
}

// fenwick

void add_accepted_depth(int depth, int value) {
    for (int i = depth + 1; i < MAXN; i += i & (-i)) {
        accepted_depths[i] += value;
    }
}

int prefix_sum_accepted_depths(int depth) {
    int res = 0;

    for (int i = depth + 1; i > 0; i -= i & (-i)) {
        res += accepted_depths[i];
    }

    return res;
}

int sum_accepted_depths(int depth) {
    return prefix_sum_accepted_depths(n) -
           (depth > 0 ? prefix_sum_accepted_depths(depth - 1) : 0);
}

// solver

void solutions_dfs_add(int node, int parent, int depth, int value) {
    int accepted = customer_max_distance[node] - depth;
    if (accepted >= 0) {
        add_accepted_depth(accepted, value);
    }

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            solutions_dfs_add(j, node, depth + 1, value);
        }
    }
}

void solutions_dfs_sum(int node, int parent, int depth) {
    solutions[node] += sum_accepted_depths(depth);

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            solutions_dfs_sum(j, node, depth + 1);
        }
    }
}

void _compute_solutions(int node) {
    solutions_dfs_add(node, node, 0, 1);

    solutions[node] += sum_accepted_depths(0);

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            solutions_dfs_add(j, node, 1, -1);

            solutions_dfs_sum(j, node, 1);
            solutions_dfs_add(j, node, 1, 1);
        }
    }

    solutions_dfs_add(node, node, 0, -1);

    centroid_used[node] = true;

    for (auto j : centroid_graph[node]) {
        if (!centroid_used[j]) {
            _compute_solutions(j);
        }
    }
}

void compute_solutions() {
    fill(centroid_used, centroid_used + n, false);
    _compute_solutions(centroid_root);
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();
    int k = fastin();

    for (int i = 0; i < n - 1; i++) {
        int a = fastin() - 1, b = fastin() - 1;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < k; i++) {
        int node = fastin() - 1;
        shop[node] = true;
    }

    for (int i = 0; i < n; i++) {
        int favorite = fastin() - 1, patience = fastin();
        customers[i] = {favorite, patience};
    }

    build_lca();
    centroid_root = centroid_decomposition(0);
    centroid_add_shops();

    for (int i = 0; i < n; i++) {
        int nearest_distance = get_nearest_shop_distance(i);
        int favorite_distance = lca_get_distance(i, customers[i].first);

        customer_max_distance[i] =
            min(nearest_distance, favorite_distance - customers[i].second - 1);
    }

    compute_solutions();
    for (int i = 0; i < n; i++) {
        cout << solutions[i] << " \n"[i + 1 == n];
    }
}
