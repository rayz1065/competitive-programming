#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN];
ll distances_sum[MAXN];

int subtree_size[MAXN];
int subtree_size_parent[MAXN];
bool centroid_used[MAXN];

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

pair<int, ll> dfs_get_distance_sum(int node, int parent) {
    int count = 1;
    ll distance_sum = 0;

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            int sub_count;
            ll sub_distance_sum;
            tie(sub_count, sub_distance_sum) = dfs_get_distance_sum(j, node);

            count += sub_count;
            distance_sum += sub_distance_sum;
        }
    }

    return {count, distance_sum + count};
}

void dfs_store_distances_sum(int node, int parent, int nodes_count,
                             ll distance) {
    distances_sum[node] = distances_sum[node] + distance;

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            dfs_store_distances_sum(j, node, nodes_count,
                                    distance + nodes_count);
        }
    }
}

void centroid_decompose(int node) {
    int tree_size = get_subtree_size(node, node);
    node = get_centroid(node, node, tree_size);

    vector<pair<int, pair<int, ll>>> children;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            children.push_back({
                j,
                dfs_get_distance_sum(j, node),
            });
        }
    }

    int count = 1;
    ll distance_sum = 0;

    for (auto child : children) {
        count += child.second.first;
        distance_sum += child.second.second;
    }

    distances_sum[node] += distance_sum;

    for (auto [j, sub_result] : children) {
        int sub_count;
        ll sub_distance_sum;
        tie(sub_count, sub_distance_sum) = sub_result;

        dfs_store_distances_sum(
            j, node, count - sub_count,
            distance_sum - sub_distance_sum + count - sub_count);
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
        cout << distances_sum[i] << " \n"[i + 1 == n];
    }
}
