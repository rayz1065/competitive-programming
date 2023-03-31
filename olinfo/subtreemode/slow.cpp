#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1000005

using namespace std;

struct NodeInfo {
    int best_color;
    unordered_map<int, int> freqs;
};

vector<int> color;
vector<int> parent;
vector<int> graph[MAXN];
vector<int> sol;

inline bool compare_freqs (NodeInfo *info, int color_new) {
    int new_freq = info->freqs[color_new];
    int old_freq = info->freqs[info->best_color];
    return new_freq > old_freq || \
          (new_freq == old_freq && color_new < info->best_color);
}

NodeInfo *get_freqs (int node) {
    NodeInfo *node_info = NULL;
    if (graph[node].size() == 0) {
        node_info = new NodeInfo();
        node_info->best_color = color[node];
        node_info->freqs[color[node]] = 1;
        sol[node] = node_info->best_color;
        return node_info;
    }
    vector<NodeInfo*> infos(graph[node].size() - 1);
    int infos_count = 0;
    for (auto i: graph[node]) {
        auto info = get_freqs(i);
        if (node_info == NULL) {
            node_info = info;
        } else if (info->freqs.size() > node_info->freqs.size()) {
            infos[infos_count++] = node_info;
            node_info = info;
        } else {
            infos[infos_count++] = info;
        }
    }
    node_info->freqs[color[node]] += 1;
    if (compare_freqs(node_info, color[node])) {
        // node color overtakes as best
        node_info->best_color = color[node];
    }
    for (auto info: infos) {
        for (auto f: info->freqs) {
            node_info->freqs[f.first] += f.second;
            if (compare_freqs(node_info, f.first)) {
                // merged overtakes as best
                node_info->best_color = f.first;
            }
        }
    }
    sol[node] = node_info->best_color;
    return node_info;
}

vector<int> solve(int n, vector<int> p, vector<int> a) {
    color = a;
    parent = p;
    for (int i = 1; i < n; i++) {
        graph[p[i]].push_back(i);
    }
    sol.resize(n);
    auto info = get_freqs(0);
    return sol;
}
