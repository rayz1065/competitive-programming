#include <bits/stdc++.h>
#define MAXN 5005

using namespace std;

int n_nodes, k_swaps;
int numbers[MAXN];
int cc_count;
int cc[MAXN];
bool adj_mat[MAXN][MAXN];

void assp () {
    for (int k = 0; k < n_nodes; k++) {
        for (int i = 0; i < n_nodes; i++) {
            for (int j = 0; j < n_nodes; j++) {
                adj_mat[i][j] = adj_mat[i][j] || (adj_mat[i][k] && adj_mat[k][j]);
            }
        }
    }
}

void cc_dfs (int i, int cc_idx) {
    if (cc[i]) {
        return ;
    }
    cc[i] = cc_idx;
    for (int j = 0; j < n_nodes; j++) {
        if (adj_mat[i][j]) {
            cc_dfs(j, cc_idx);
        }
    }
}

void find_ccs () {
    cc_count = 0;
    for (int i = 0; i < n_nodes; i++) {
        if (!cc[i]) {
            cc_dfs(i, ++cc_count);
        }
    }
}

void bubble_sort () {
    for (int i = 0; i < n_nodes; i++) {
        for (int j = 0; j < n_nodes; j++) {
            if (numbers[i] < numbers[j] && cc[i] == cc[j]) {
                swap(numbers[i], numbers[j]);
            }
        }
    }
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n_nodes >> k_swaps;

    for (int i = 0; i < n_nodes; i++) {
        cin >> numbers[i];
    }
    for (int i = 0; i < k_swaps; i++) {
        int swap_dist;
        cin >> swap_dist;
        for (int j = 0; j < n_nodes; j++) {
            if (j + swap_dist < n_nodes) {
                adj_mat[j][j + swap_dist] = true;
                adj_mat[j + swap_dist][j] = true;
            }
        }
    }

    // assp();
    find_ccs();
    bubble_sort();

    for (int i = 0; i < n_nodes; i++) {
        cout << numbers[i] << " \n"[i + 1 == n_nodes];
    }
}
