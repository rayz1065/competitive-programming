#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 200005
#define HALF_MAXN (MAXN / 2)

using namespace std;

FILE *fin, *fout;
int n_nodes, m_branches;
vector<int> graph[MAXN];
int dfs_parent[MAXN];
int dfs_num[MAXN];
int sol[MAXN];

int fastin() {
    int v = 0;
    char c = fgetc(fin);
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = fgetc(fin);
    }
    return v;
}

int find_cycle (int node) {
    assert(dfs_num[node] == 0);
    dfs_num[node] = 1;
    for (auto j: graph[node]) {
        if (dfs_num[j] == 0) {
            dfs_parent[j] = node;
            int res = find_cycle(j);
            if (res != -1) {
                return res;
            }
        } else if (dfs_num[j] == 1) {
            // this forms a loop
            return node;
        }
    }
    dfs_num[node] = 2;
    return -1;
}

int main () {
#ifdef DEBUG
    fin = stdin;
    fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    n_nodes = fastin();
    m_branches = fastin();
    for (int i = 0; i < n_nodes; i++) {
        int a, b;
        a = fastin();
        b = fastin();
        sol[a] = b;
        b += HALF_MAXN;
        graph[a].push_back(b);
    }
    for (int i = 0; i < m_branches - n_nodes; i++) {
        int a, b;
        a = fastin();
        b = fastin() + HALF_MAXN;
        graph[b].push_back(a);
    }
    for (int i = 0; i < n_nodes; i++) {
        if (dfs_num[i]) {
            continue ;
        }
        int node = find_cycle(i);
        cout << "Found cycle ending at " << node << "\n";
        if (node != -1) {
            int last_node = -1;
            for (auto j: graph[node]) {
                if (dfs_num[j] == 1) {
                    last_node = j;
                    break ;
                }
            }
            // from i we want to go to node instead
            sol[last_node] = node - HALF_MAXN;
            node = dfs_parent[node];
            // node is now on the left 0 <= node < HALF_MAXN
            while (node != last_node) {
                // node = dfs_parent[node];
                sol[node] = dfs_parent[node] - HALF_MAXN;
                node = dfs_parent[node];
                node = dfs_parent[node];
            }
            for (int i = 0; i < n_nodes; i++) {
                fprintf(fout, "%d %d\n", i, sol[i]);
            }
            return 0;
        }
    }
    fprintf(fout, "-1\n");
}