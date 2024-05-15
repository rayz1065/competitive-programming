#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, queries_n;
vector<int> graph[MAXN];

vector<pair<int, int>> queries;  // node, time
vector<int> roots;

int subtree_size[MAXN];
bool centroid_used[MAXN];
vector<pair<int, int>> centroid_ancestors[MAXN];  // ancestor, distance

pair<int, int> farthest_nodes[MAXN][3];  // child, distance

int get_subtree_size(int node, int parent) {
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

void centroid_get_distances(int node, int parent, int centroid, int distance) {
    centroid_ancestors[node].push_back({centroid, distance});

    for (auto j : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            centroid_get_distances(j, node, centroid, distance + 1);
        }
    }
}

void centroid_decompose(int node) {
    int tree_size = get_subtree_size(node, node);
    node = get_centroid(node, node, tree_size);

    centroid_get_distances(node, node, node, 0);
    centroid_used[node] = true;

    for (auto j : graph[node]) {
        if (!centroid_used[j]) {
            centroid_decompose(j);
        }
    }
}

void add_node(int node) {
    int previous_centroid = -1;

    for (auto [j, distance] : centroid_ancestors[node]) {
        farthest_nodes[j][2] = {previous_centroid, distance};

        for (int order = 1; order >= 0; order--) {
            // sort based on distance
            if (farthest_nodes[j][order + 1].second <
                farthest_nodes[j][order].second) {
                break;
            }
            swap(farthest_nodes[j][order + 1], farthest_nodes[j][order]);
        }

        if (farthest_nodes[j][0].first == farthest_nodes[j][1].first) {
            // ensure one is different
            swap(farthest_nodes[j][1], farthest_nodes[j][2]);
        }

        previous_centroid = j;
    }
}

int get_farthest_node(int node) {
    int res = 0;
    int previous_centroid = -2;  // allow picking own farthest as well

    for (auto [j, distance] : centroid_ancestors[node]) {
        for (int order = 0; order < 2; order++) {
            if (farthest_nodes[j][order].first == previous_centroid) {
                // double counting edges
                continue;
            }

            res = max(res, distance + farthest_nodes[j][order].second);
        }

        previous_centroid = j;
    }

    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("newbarn.in", ios::in);
    cout.open("newbarn.out", ios::out);
#endif
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> q;

    while (q--) {
        char op;
        int node;
        cin >> op >> node;
        node--;

        if (op == 'B') {
            if (node == -2) {
                roots.push_back(n);
            } else {
                graph[node].push_back(n);
                graph[n].push_back(node);
            }
            n += 1;
        } else {
            queries.push_back({node, n - 1});
            queries_n += 1;
        }
    }

    for (auto node : roots) {
        centroid_decompose(node);
    }

    for (int node = 0; node < n; node++) {
        for (int order = 0; order < 2; order++) {
            farthest_nodes[node][order] = {-1, INT_MIN >> 1};
        }
        reverse(centroid_ancestors[node].begin(),
                centroid_ancestors[node].end());
    }

    int next_to_add = 0;

    for (auto [node, new_time] : queries) {
        while (next_to_add <= new_time) {
            add_node(next_to_add++);
        }

        cout << get_farthest_node(node) << "\n";
    }
}
