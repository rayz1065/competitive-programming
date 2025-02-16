#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

int found_at_depth[MAXN];
int cut_at_depth[MAXN];

vector<int> graph[MAXN];

int dfs(int i, int depth) {
    int max_child_depth = depth;

    for (auto j : graph[i]) {
        max_child_depth = max(max_child_depth, dfs(j, depth + 1));
    }

    found_at_depth[depth] += 1;
    cut_at_depth[max_child_depth + 1] += 1;

    return max_child_depth;
}

int pota(int n, vector<int> parent) {
    for (int i = 1; i < n; i++) {
        graph[parent[i]].push_back(i);
    }

    dfs(0, 0);

    int curr = 0, best = 0;

    for (int i = 0; i < n; i++) {
        curr += found_at_depth[i];
        curr -= cut_at_depth[i];
        best = max(best, curr);
    }

    return n - best;
}
