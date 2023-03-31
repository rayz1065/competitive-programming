#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, t;
bool visited[MAXN];
int parent_dist[MAXN];
int parent[MAXN];
int depth[MAXN];
int lca_anc[20][MAXN];
long long lca_info[20][MAXN];
long long lca_max_up[20][MAXN];
long long lca_max_mid[20][MAXN];
long long lca_max_down[20][MAXN];

struct Branch {
    int to;
    int weight;
};
vector<Branch> graph[MAXN];
void dfs (int node) {
    visited[node] = true;
    for (auto branch: graph[node]) {
        if (!visited[branch.to]) {
            depth[branch.to] = depth[node] + 1;
            parent[branch.to] = node;
            parent_dist[branch.to] = branch.weight;
            dfs(branch.to);
        }
    }
}

void init_lca () {
    for (int i = 0; i < n; i++) {
        lca_anc[0][i] = parent[i];
        if (t == 0) {
            lca_info[0][i] = 1;
        } else if (t == 1 || t == 2 || t == 3) {
            lca_info[0][i] = parent_dist[i];
        }
        if (t == 3) {
            long long val = max(lca_info[0][i], 0ll);
            lca_max_up[0][i] = val;
            lca_max_mid[0][i] = val;
            lca_max_down[0][i] = val;
        }
    }
    for (int k = 1; k < 20; k++) {
        for (int i = 0; i < n; i++) {
            lca_anc[k][i] = -1;
            int anc = lca_anc[k - 1][i];
            if (anc == -1) {
                continue ;
            }
            int anc_anc = lca_anc[k - 1][anc];
            if (anc_anc == -1) {
                continue ;
            }
            lca_anc[k][i] = anc_anc;

            // compute extra information...
            if (t == 0 || t == 1 || t == 3) {
                lca_info[k][i] = lca_info[k - 1][i] + lca_info[k - 1][anc];
            } else if (t == 2) {
                lca_info[k][i] = min(lca_info[k - 1][i], lca_info[k - 1][anc]);
            }

            if (t == 3) {
                // calculate best segments
                lca_max_mid[k][i] = max(lca_max_mid[k - 1][i], lca_max_mid[k - 1][anc]);
                lca_max_mid[k][i] = max(lca_max_mid[k][i], lca_max_up[k - 1][i] + lca_max_down[k - 1][anc]);
                lca_max_down[k][i] = max(lca_max_down[k - 1][i], lca_info[k - 1][i] + lca_max_down[k - 1][anc]);
                lca_max_up[k][i] = max(lca_max_up[k - 1][anc], lca_info[k - 1][anc] + lca_max_up[k - 1][i]);
            }
        }
    }
    // for (int k = 0; k < 3; k++) {
    //     for (int i = 0; i < n; i++) {
    //         if (lca_anc[k][i] == -1) {
    //             continue ;
    //         }
    //         printf("[%d, i=%d] %d (mid=%d, up=%d, down=%d)\n", k, i, lca_info[k][i], lca_max_mid[k][i], lca_max_up[k][i], lca_max_down[k][i]);
    //     }
    // }
}

long long get_lca (int i, int j) {
    // make j the deeper node
    long long res = t == 2 ? INT_MAX >> 1 : 0;
    long long i_max_up = 0;
    long long j_max_up = 0;
    if (depth[i] > depth[j]) {
        swap(i, j);
    }
    // equalize the depths
    for (int k = 0; k < 20; k++) {
        if ((depth[j] - depth[i]) & (1 << k)) {
            if (t == 0 || t == 1) {
                res += lca_info[k][j];
            } else if (t == 2) {
                res = min(res, lca_info[k][j]);
            } else {
                res = max(res, j_max_up + lca_max_down[k][j]);
                res = max(res, lca_max_mid[k][j]);
                j_max_up = max(lca_max_up[k][j], lca_info[k][j] + j_max_up);
                res = max(res, j_max_up);
            }
            j = lca_anc[k][j];
        }
    }
    if (i == j) {
        return res;
    }
    // move up
    for (int k = 19; k >= 0; k--) {
        if (lca_anc[k][i] != lca_anc[k][j]) {
            if (t == 0 || t == 1) {
                res += lca_info[k][i];
                res += lca_info[k][j];
            } else if (t == 2) {
                res = min(res, lca_info[k][i]);
                res = min(res, lca_info[k][j]);
            } else {
                res = max(res, j_max_up + lca_max_down[k][j]);
                res = max(res, lca_max_mid[k][j]);
                j_max_up = max(lca_max_up[k][j], lca_info[k][j] + j_max_up);
                res = max(res, j_max_up);
                res = max(res, i_max_up + lca_max_down[k][i]);
                res = max(res, lca_max_mid[k][i]);
                i_max_up = max(lca_max_up[k][i], lca_info[k][i] + i_max_up);
                res = max(res, i_max_up);
            }
            i = lca_anc[k][i], j = lca_anc[k][j];
        }
    }
    if (t == 0 || t == 1) {
        res += lca_info[0][i];
        res += lca_info[0][j];
    }  else if (t == 2) {
        res = min(res, lca_info[0][i]);
        res = min(res, lca_info[0][j]);
    } else {
        res = max(res, j_max_up + lca_max_down[0][j]);
        res = max(res, lca_max_mid[0][j]);
        j_max_up = max(lca_max_up[0][j], lca_info[0][j] + j_max_up);
        res = max(res, j_max_up);
        res = max(res, lca_max_mid[0][i]);
        res = max(res, i_max_up + lca_max_down[0][i]);
        i_max_up = max(lca_max_up[0][i], lca_info[0][i] + i_max_up);
        res = max(res, i_max_up);
        res = max(res, i_max_up + j_max_up);
    }
    return res;
}

void inizia(int N, int T, int A[], int B[], int C[]) {
    n = N;
    t = T;
    for (int i = 0; i < n - 1; i++) {
        graph[A[i]].push_back({ B[i], C[i] });
        graph[B[i]].push_back({ A[i], C[i] });
    }
    fill(parent, parent + n, -1);
    dfs(0);
    init_lca();
    return ;
}

long long int distanza1(int u, int v) {
    return get_lca(u, v);
}

long long int distanza2(int u, int v) {
    return get_lca(u, v);
}

long long int minimo(int u, int v) {
    return get_lca(u, v);
}

long long int massimo(int u, int v) {
    return get_lca(u, v);
}
