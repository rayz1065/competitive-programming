#include <bits/stdc++.h>
#define MAXN 100005
#define LOGMAXN 20

using namespace std;

int n;
vector<int> graph[MAXN];

// centroid tree
int nearest_red[MAXN];  // nearest red within the centroid subtree
int subtree_size[MAXN];
bool centroid_used[MAXN];
vector<pair<int, int>> centroid_ancestors[MAXN];

int get_subtree_size(int node, int parent) {
    subtree_size[node] = 1;

    for (auto v : graph[node]) {
        if (v == parent || centroid_used[node]) {
            continue;
        }

        subtree_size[node] += get_subtree_size(v, node);
    }

    return subtree_size[node];
}

int get_centroid(int node, int parent, int tree_size) {
    for (auto v : graph[node]) {
        if (v == parent || centroid_used[v]) {
            continue;
        }

        if (subtree_size[v] >= tree_size / 2) {
            return get_centroid(v, node, tree_size);
        }
    }

    return node;
}

void compute_distances(int node, int centroid, int parent, int curr_distance) {
    centroid_ancestors[node].push_back({centroid, curr_distance});

    for (auto v : graph[node]) {
        if (centroid_used[v] || v == parent) {
            continue;
        }

        compute_distances(v, centroid, node, curr_distance + 1);
    }
}

int build_centroid_tree(int node) {
    int tree_size = get_subtree_size(node, node);
    int centroid = get_centroid(node, node, tree_size);

    compute_distances(centroid, centroid, centroid, 0);

    centroid_used[centroid] = true;

    for (auto v : graph[centroid]) {
        if (centroid_used[v]) {
            continue;
        }

        int v_centroid = build_centroid_tree(v);
    }

    return centroid;
}

void update_distance(int node, int newly_colored) {
    for (auto ancestor : centroid_ancestors[node]) {
        nearest_red[ancestor.first] =
            min(nearest_red[ancestor.first], ancestor.second);
    }
}

void color_node(int node) { update_distance(node, node); }

int get_nearest_red(int node) {
    int best = INT_MAX >> 1;

    for (auto ancestor : centroid_ancestors[node]) {
        int new_dist = ancestor.second + nearest_red[ancestor.first];
        best = min(best, new_dist);
    }

    return best;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q_queries;
    cin >> n >> q_queries;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    build_centroid_tree(1);

    fill(nearest_red, nearest_red + n + 1, INT_MAX >> 1);
    color_node(1);

    while (q_queries--) {
        int t, v;
        cin >> t >> v;

        if (t == 1) {
            // paint v in red
            color_node(v);
        } else {
            // distance from v to red
            cout << get_nearest_red(v) << "\n";
        }
    }
}
