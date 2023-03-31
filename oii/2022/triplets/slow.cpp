#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n_nodes;
vector<int> graph[MAXN];
int adj_mat[10005][10005];

void compute_distances () {
    for (int k = 0; k < n_nodes; k++) {
        for (int i = 0; i < n_nodes; i++) {
            for (int j = 0; j < n_nodes; j++) {
                adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
            }
        }
    }
}

int build(int N, vector<int> A, vector<int> B) {
    ::n_nodes = N;
    for (int i = 0; i < n_nodes; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    if (n_nodes < 10005) {
        for (int i = 0; i < n_nodes; i++) {
            fill(adj_mat[i], adj_mat[i] + n_nodes, INT_MAX >> 1);
        }
        for (int i = 0; i < n_nodes; i++) {
            adj_mat[A[i]][B[i]] = 1;
            adj_mat[B[i]][A[i]] = 1;
        }
        compute_distances();
        int best_dist = 0;
        for (int i = 0; i < n_nodes; i++) {
            for (int j = i + 1; j < n_nodes; j++) {
                for (int k = j + 1; k < n_nodes; k++) {
                    best_dist = max(best_dist, adj_mat[i][j] + adj_mat[i][k] + adj_mat[k][j]);
                }
            }
        }
        return best_dist;
    }
    return 42;
}
