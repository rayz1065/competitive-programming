#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n_nodes;
vector<int> graph[MAXN];
bool visited[MAXN];

struct NodeInfo {
    int max_depth; // deepest node underneath
    int best_sol; // best triplet
    int best_pair; // max(dist(a, b) + dist(a) + dist(b))
    int node;
};

bool sort_by_depth (const NodeInfo &a, const NodeInfo &b) {
    return a.max_depth > b.max_depth;
}

bool sort_by_pair (const NodeInfo &a, const NodeInfo &b) {
    return a.best_pair > b.best_pair;
}

NodeInfo solve (int node) {
#ifdef DEBUG
    cout << "Visit " << node << " with " << graph[node].size() << " neigh\n";
#endif
    visited[node] = true;
    vector<NodeInfo> children_info;
    for (auto i: graph[node]) {
        if (!visited[i]) {
            children_info.push_back(solve(i));
        }
    }
    vector<NodeInfo> depth_order = children_info;
    sort(depth_order.begin(), depth_order.end(), sort_by_depth);
    vector<NodeInfo> pair_order = children_info;
    sort(pair_order.begin(), pair_order.end(), sort_by_pair);

    // calculate the deepest node
    int max_depth = 0; // default, the node itself
    for (auto info: depth_order) {
        max_depth = max(max_depth, info.max_depth + 1);
    }

    // calculate the best pair
    int best_pair = INT_MIN; // none
    for (int i = 0; i < children_info.size(); i++) {
        auto info1 = children_info[i];
        // take the root and the deepest
        best_pair = max(best_pair, (info1.max_depth + 1) * 2);
        // take the best pair underneath
        best_pair = max(best_pair, info1.best_pair + 2);
    }
    // take the 2 deepest nodes
    if (depth_order.size() >= 2) {
        auto info1 = depth_order[0];
        auto info2 = depth_order[1];
        best_pair = max(best_pair, ((info1.max_depth + 1) + (info2.max_depth + 1)) * 2);
    }

    int best_sol = INT_MIN; // none
    // calculate the best triplet
    for (int i = 0; i < children_info.size(); i++) {
        auto info1 = children_info[i];
        // take the pair a,b and the root
        best_sol = max(best_sol, info1.best_pair + 2);
        // just take the same sol
        best_sol = max(best_sol, info1.best_sol);
    }

    if (depth_order.size() >= 2) {
        // take the best pair and the deepest
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                auto info1 = depth_order[i];
                auto info2 = pair_order[j];
                if (info1.node != info2.node) {
                    best_sol = max(best_sol, (info1.best_pair + 2) + (info2.max_depth + 1) * 2);
                    best_sol = max(best_sol, (info2.best_pair + 2) + (info1.max_depth + 1) * 2);
                }
            }
        }
    }
    // take the two deepest and the root
    if (depth_order.size() >= 2) {
        auto info1 = depth_order[0];
        auto info2 = depth_order[1];
        best_sol = max(best_sol, ((info1.max_depth + 1) + (info2.max_depth + 1)) * 2);
    }

    // take the three deepest nodes
    if (depth_order.size() >= 3) {
        best_sol = max(best_sol, ((depth_order[0].max_depth + 1) +
                                  (depth_order[1].max_depth + 1) +
                                  (depth_order[2].max_depth + 1)) * 2);
    }

#ifdef DEBUG
    printf("%d depth=%d, pair=%d, sol=%d\n", node, max_depth, best_pair, best_sol);
#endif
    return { max_depth, best_sol, best_pair, node };
}

int build(int N, vector<int> A, vector<int> B) {
    ::n_nodes = N;
    for (int i = 0; i < n_nodes - 1; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }

    auto info = solve(0);
    return info.best_sol;
}
