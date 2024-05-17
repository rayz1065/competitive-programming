#include <bits/stdc++.h>
#define MAXN 200005
#define LOGMAXN 20

using namespace std;

int n;
int up[MAXN][LOGMAXN];
int depth[MAXN];
vector<int> graph[MAXN];

void lca_dfs(int node) {
    for (auto j : graph[node]) {
        if (up[node][0] != j) {
            up[j][0] = node;
            depth[j] = depth[node] + 1;
            lca_dfs(j);
        }
    }
}

void make_lca() {
    lca_dfs(0);

    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[i][j - 1] == -1 ? -1 : up[up[i][j - 1]][j - 1];
        }
    }
}

int find_ancestor(int a, int distance) {
    if (depth[a] < distance) {
        return -1;
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int new_depth = depth[a] - (1 << j);
        if (distance - (1 << j) >= 0) {
            distance -= (1 << j);
            a = up[a][j];
        }
    }

    return a;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--;
        graph[parent].push_back(i);
    }

    make_lca();

    while (q--) {
        int node, distance;
        cin >> node >> distance;
        node--;

        int ancestor = find_ancestor(node, distance);
        cout << (ancestor == -1 ? -1 : ancestor + 1) << "\n";
    }
}
