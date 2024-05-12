#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN];
int subtree_size[MAXN];
int new_house[MAXN];

ll dfs(int node, int parent, int depth) {
    ll res = depth;

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }

        res += dfs(j, node, depth + 1);
    }

    return res;
}

int get_subtree_size(int node, int parent) {
    subtree_size[node] = 1;

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }

        subtree_size[node] += get_subtree_size(j, node);
    }

    return subtree_size[node];
}

int get_centroid(int node, int parent, int tree_size) {
    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }

        if (subtree_size[j] > tree_size / 2) {
            return get_centroid(j, node, tree_size);
        }
    }

    return node;
}

void grab_nodes(int node, int parent, queue<int> &free_nodes) {
    free_nodes.push(node);

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }

        grab_nodes(j, node, free_nodes);
    }
}

void assign_house(int node, queue<int> &free_nodes) {
    int new_resident = free_nodes.front();
    free_nodes.pop();
    new_house[new_resident] = node;
}

void replace_nodes(int node, int parent, queue<int> &free_nodes) {
    assign_house(node, free_nodes);

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }

        replace_nodes(j, node, free_nodes);
    }
}

ll solve() {
    int tree_size = get_subtree_size(0, 0);
    int centroid = get_centroid(0, 0, tree_size);
    get_subtree_size(centroid, centroid);

    int largest_subtree_root = -1, largest_subtree_size = -1;
    for (auto j : graph[centroid]) {
        if (subtree_size[j] > largest_subtree_size) {
            largest_subtree_size = subtree_size[j];
            largest_subtree_root = j;
        }
    }

    queue<int> free_nodes;
    grab_nodes(largest_subtree_root, centroid, free_nodes);
    assign_house(centroid, free_nodes);

    free_nodes.push(centroid);

    for (auto j : graph[centroid]) {
        if (j == largest_subtree_root) {
            continue;
        }

        replace_nodes(j, centroid, free_nodes);
        grab_nodes(j, centroid, free_nodes);
    }

    replace_nodes(largest_subtree_root, centroid, free_nodes);

    return dfs(centroid, centroid, 0) * 2;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << solve() << "\n";
    for (int i = 0; i < n; i++) {
        cout << new_house[i] + 1 << " \n"[i + 1 == n];
    }
}
