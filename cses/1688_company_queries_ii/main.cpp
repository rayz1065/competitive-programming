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

int find_lca(int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a, b);
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int new_depth = depth[b] - (1 << j);
        if (new_depth >= depth[a]) {
            b = up[b][j];
        }
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j], b = up[b][j];
        }
    }

    return a == b ? a : up[a][0];
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;

    up[0][0] = -1;
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--;
        graph[parent].push_back(i);
    }

    make_lca();

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << find_lca(a, b) + 1 << "\n";
    }
}
