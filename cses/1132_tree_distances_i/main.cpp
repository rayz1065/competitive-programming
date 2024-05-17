#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];
int farthest_node[MAXN];

int subtree_size[MAXN];
int subtree_size_parent[MAXN];
bool centroid_used[MAXN];
vector<pair<int, int>> centroid_anc[MAXN];

int get_subtree_size(int node, int parent) {
    if (subtree_size_parent[node] == parent + 1) {
        return subtree_size[node];
    }

    subtree_size_parent[node] = parent + 1;
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

int dfs_get_max_distance(int node, int parent, int distance) {
    int res = distance;

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            res = max(res, dfs_get_max_distance(j, node, distance + 1));
        }
    }

    return res;
}

void dfs_store_max_distance(int node, int parent, int distance) {
    farthest_node[node] = max(farthest_node[node], distance);

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            dfs_store_max_distance(j, node, distance + 1);
        }
    }
}

void centroid_decompose(int node) {
    int tree_size = get_subtree_size(node, node);
    node = get_centroid(node, node, tree_size);

    vector<pair<int, int>> distances;
    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            distances.push_back({dfs_get_max_distance(j, node, 1), j});
        }
    }
    distances.push_back({0, node});

    sort(distances.begin(), distances.end());
    reverse(distances.begin(), distances.end());

    farthest_node[node] = max(farthest_node[node], distances[0].first);

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            int distance = 0;

            for (int i = 0; i < 2 && i < distances.size(); i++) {
                if (j != distances[i].second) {
                    distance = max(distance, distances[i].first);
                }
            }

            dfs_store_max_distance(j, node, distance + 1);
        }
    }

    centroid_used[node] = true;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            centroid_decompose(j);
        }
    }
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
    for (int i = 0; i < n - 1; i++) {
        int a = fastin() - 1, b = fastin() - 1;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    centroid_decompose(0);

    for (int i = 0; i < n; i++) {
        cout << farthest_node[i] << " \n"[i + 1 == n];
    }
}
