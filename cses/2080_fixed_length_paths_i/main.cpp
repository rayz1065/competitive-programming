#include <bits/stdc++.h>
#define MAXN 200005
#pragma GCC optimize("Ofast")

using namespace std;

typedef long long ll;

int n, k;
vector<int> graph[MAXN];

bool centroid_used[MAXN];
int subtree_size[MAXN];
int subtree_cached_parent[MAXN];
int counts[MAXN];

ll found_paths = 0;

int get_subtree_size(int node, int parent) {
    if (subtree_cached_parent[node] == parent + 1) {
        return subtree_size[node];
    }
    subtree_cached_parent[node] = parent + 1;

    int res = 1;

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            res += get_subtree_size(j, node);
        }
    }

    return subtree_size[node] = res;
}

int get_centroid(int node, int parent, int tree_size) {
    bool found = true;

    while (found) {
        found = false;

        for (auto j : graph[node]) {
            if (j != parent && !centroid_used[j] &&
                subtree_size[j] > tree_size / 2) {
                found = true;
                parent = node;
                node = j;
                break;
            }
        }
    }

    return node;
}

void dfs_increment(int node, int parent, int distance, int delta) {
    if (distance > k) {
        return;
    }

    counts[distance] += delta;

    if (distance == k) {
        return;
    }

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            dfs_increment(j, node, distance + 1, delta);
        }
    }
}

void dfs_solve(int node, int parent, int distance) {
    if (distance > k) {
        return;
    }

    found_paths += counts[k - distance];

    if (distance == k) {
        return;
    }

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            dfs_solve(j, node, distance + 1);
        }
    }
}

void _compute_combinations(int node) {
    dfs_increment(node, node, 0, 1);

    found_paths += counts[k];

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            dfs_increment(j, node, 1, -1);
            dfs_solve(j, node, 1);
            dfs_increment(j, node, 1, 1);
        }
    }

    dfs_increment(node, node, 0, -1);
}

void centroid_decompose(int node) {
    int tree_size = get_subtree_size(node, node);
    if (tree_size < k) {
        return;  // 4x speed-boost 🤦
    }

    node = get_centroid(node, node, tree_size);

    _compute_combinations(node);

    centroid_used[node] = true;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            centroid_decompose(j);
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    centroid_decompose(0);

    cout << found_paths / 2 << "\n";
}
