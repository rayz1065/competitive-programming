#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> graph[MAXN];

int subtree_size[MAXN];
bool centroid_used[MAXN];

int found_imbalance_levels[MAXN * 2][2];  // imbalance, tail_balanced

int get_subtree_size(int node, int parent) {
    subtree_size[node] = 1;

    for (auto [j, color] : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            subtree_size[node] += get_subtree_size(j, node);
        }
    }

    return subtree_size[node];
}

int get_centroid(int node, int parent, int tree_size) {
    for (auto [j, color] : graph[node]) {
        if (j != parent && !centroid_used[j] &&
            subtree_size[j] > tree_size / 2) {
            return get_centroid(j, node, tree_size);
        }
    }

    return node;
}

void add_imbalance_levels(int node, int parent, int imbalance,
                          int min_imbalance, int max_imbalance, int value) {
    // on the path we found `[-min_imbalance, max_imbalance]`
    // the current imbalance is `imbalance`
    // if we can find the symmetric imbalance, this tail is balanced
    // when min_imbalance = max_imbalance we are at the root
    bool tail_balanced = min_imbalance <= imbalance &&
                         imbalance <= max_imbalance &&
                         min_imbalance != max_imbalance;
    found_imbalance_levels[imbalance + MAXN][tail_balanced] += value;

    min_imbalance = min(min_imbalance, imbalance);
    max_imbalance = max(max_imbalance, imbalance);

    for (auto [j, color] : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            int new_imbalance = imbalance + color;
            add_imbalance_levels(j, node, new_imbalance, min_imbalance,
                                 max_imbalance, value);
        }
    }
}

ll bi_balanced_dfs(int node, int parent, int imbalance, int min_imbalance,
                   int max_imbalance, bool head_balanced) {
    bool tail_balanced = min_imbalance <= imbalance &&
                         imbalance <= max_imbalance &&
                         min_imbalance != max_imbalance;

    min_imbalance = min(min_imbalance, imbalance);
    max_imbalance = max(max_imbalance, imbalance);

    ll res = found_imbalance_levels[-imbalance + MAXN][1];
    if (tail_balanced) {
        res += found_imbalance_levels[-imbalance + MAXN][0];
    }

    if (head_balanced && tail_balanced && imbalance == 0) {
        // double count for the root
        res += 2;
    }

    head_balanced = head_balanced || imbalance == 0;

    for (auto [j, color] : graph[node]) {
        if (j != parent && !centroid_used[j]) {
            int new_imbalance = imbalance + color;
            res += bi_balanced_dfs(j, node, new_imbalance, min_imbalance,
                                   max_imbalance, head_balanced);
        }
    }

    return res;
}

ll count_bi_balanced_paths(int node) {
    add_imbalance_levels(node, node, 0, 0, 0, 1);
    found_imbalance_levels[MAXN][0] -= 1;

    ll res = 0;

    for (auto [j, color] : graph[node]) {
        if (centroid_used[j]) {
            continue;
        }

        add_imbalance_levels(j, node, color, 0, 0, -1);

        res += bi_balanced_dfs(j, node, color, 0, 0, false);

        add_imbalance_levels(j, node, color, 0, 0, 1);
    }

    found_imbalance_levels[MAXN][0] += 1;
    add_imbalance_levels(node, node, 0, 0, 0, -1);

    return res / 2;
}

ll centroid_decomposition(int node) {
    int tree_size = get_subtree_size(node, node);
    node = get_centroid(node, node, tree_size);

    ll res = count_bi_balanced_paths(node);
    centroid_used[node] = true;

    for (auto [j, color] : graph[node]) {
        if (!centroid_used[j]) {
            res += centroid_decomposition(j);
        }
    }

    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("yinyang.in", ios::in);
    cout.open("yinyang.out", ios::out);
#endif

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, color;
        cin >> a >> b >> color;
        a--, b--;
        graph[a].push_back({b, 2 * color - 1});  // color is -1 or +1
        graph[b].push_back({a, 2 * color - 1});
    }

    cout << centroid_decomposition(0) << "\n";
}
