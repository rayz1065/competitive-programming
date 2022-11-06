#include <bits/stdc++.h>
#define MAXN 505

using namespace std;

int mf_s = 0, mf_t;
int n, adj_mat[MAXN * 2][MAXN * 2], meeting[MAXN];
vector<int> graph[MAXN * 2];
bool matched[MAXN * 2];
bool visited[MAXN * 2];
int dfs_tree[MAXN * 2];

int get_node (bool incoming, int i) {
    return incoming * n + i + 1;
}

bool _find_aug (int node) {
    if (node == mf_t) {
        return true;
    }
    visited[node] = true;
    for (auto j: graph[node]) {
        if (!visited[j] && adj_mat[node][j]) {
            visited[j] = true;
            dfs_tree[j] = node;
            if (_find_aug(j)) {
                return true;
            }
        }
    }
    return false;
}

bool find_aug () {
    fill(visited, visited + mf_t + 1, false);
    dfs_tree[mf_s] = -1;
    return _find_aug(mf_s);
}

void augment (int node) {
    if (dfs_tree[node] == -1) {
        return ;
    }
    adj_mat[dfs_tree[node]][node]--;
    adj_mat[node][dfs_tree[node]]++;
    augment(dfs_tree[node]);
}

int max_flow () {
    int mf = 0;
    while (find_aug()) {
        mf++;
        augment(mf_t);
    }
    return mf;
}

void add_branch (int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
    adj_mat[a][b] = 1;
}

int main () {
    cin >> n;
    mf_t = 2 * n + 1;
    for (int i = 0; i < n; i++) {
        cin >> meeting[i];
        add_branch(mf_s, get_node(0, i));
        add_branch(get_node(1, i), mf_t);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dist;
            cin >> dist;
            if (i != j && dist + meeting[i] <= meeting[j]) {
                add_branch(get_node(0, i), get_node(1, j));
                // cout << i << " -> " << j << "\n"; //
            }
        }
    }

    cout << n - max_flow() << "\n";
}
