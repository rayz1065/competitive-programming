#include <bits/stdc++.h>
#define MAXN 5005
#define MF_SIZE (MAXN * 2 + 5)

using namespace std;

int n_points;
struct Point {
    int comp_x;
    int comp_y;
} points[MAXN];

// compress points into a smaller space
int compressed_x_next = 0;
int uncompressed_xs[MAXN];
unordered_map<int, int> compressed_xs;

int compressed_y_next = 0;
int uncompressed_ys[MAXN];
unordered_map<int, int> compressed_ys;

// frequencies
int freq_x[MAXN];
int freq_y[MAXN];

// max flow
const int mf_source = 0;
const int mf_rows_start = 1;
const int mf_cols_start = mf_rows_start + MAXN;
const int mf_well = mf_cols_start + MAXN;
vector<int> graph[MF_SIZE];
int mf_adj_mat[MF_SIZE][MF_SIZE];

Point compress (int x, int y) {
    if (compressed_xs.find(x) == compressed_xs.end()) {
        compressed_xs[x] = compressed_x_next;
        uncompressed_xs[compressed_x_next] = x;
        compressed_x_next++;
    }
    if (compressed_ys.find(y) == compressed_ys.end()) {
        compressed_ys[y] = compressed_y_next;
        uncompressed_ys[compressed_y_next] = y;
        compressed_y_next++;
    }
    int compressed_x = compressed_xs[x];
    int compressed_y = compressed_ys[y];
    // cout << "compressed " << x << "," << y << " to " << compressed_x << "," << compressed_y << "\n";
    return { compressed_x, compressed_y };
}

int mf_row (int r) {
    return r + mf_rows_start;
}
int mf_col (int c) {
    return c + mf_cols_start;
}

void mf_add_branch (int a, int b, int w) {
    // cout << "b " << a << " -> " << b << ", w = " << w << "\n";
    graph[a].push_back(b);
    graph[b].push_back(a);
    mf_adj_mat[a][b] = w;
}

int mf_dist[MF_SIZE];
int mf_parent[MF_SIZE];

bool mf_find_augmenting () {
    queue<int> ff;
    ff.push(mf_source);
    fill(mf_dist, mf_dist + MF_SIZE, INT_MAX >> 1);
    fill(mf_parent, mf_parent + MF_SIZE, -1);
    mf_dist[mf_source] = 0;

    while (!ff.empty()) {
        int node = ff.front();
        // cout << "Visiting " << node << "\n";
        ff.pop();
        for (auto i: graph[node]) {
            // cout << node << " -> " << i << " " << mf_dist[i] << " > " << mf_dist[node] + 1 << " && " << mf_adj_mat[node][i] << " > 0\n";
            if (mf_dist[i] > mf_dist[node] + 1 && mf_adj_mat[node][i] > 0) {
                mf_dist[i] = mf_dist[node] + 1;
                mf_parent[i] = node;

                if (i == mf_well) {
                    return true;
                }

                ff.push(i);
            }
        }
    }

    return false;
}

int mf_augment (int node, int min_found) {
    int prev_node = mf_parent[node];
    // cout << "augmenting " << node << " to " << prev_node << "\n";
    if (prev_node == -1) {
        return min_found;
    }
    min_found = min(min_found, mf_adj_mat[prev_node][node]);
    min_found = mf_augment(prev_node, min_found);
    mf_adj_mat[prev_node][node] -= min_found;
    mf_adj_mat[node][prev_node] += min_found;
    return min_found;
}

int mf_find () {
    int mf = 0;
    while (mf_find_augmenting()) {
        // cout << "Found augmenting path\n";
        mf += mf_augment(mf_well, INT_MAX >> 1);
    }
    return mf;
}

int main() {
    cin >> n_points;
    for(int i = 0; i < n_points; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = compress(x, y);
        freq_x[points[i].comp_x]++;
        freq_y[points[i].comp_y]++;
    }

    // construct the mf graph
    for (int i = 0; i < compressed_x_next; i++) {
        if (freq_x[i] % 3 != 0) {
            cout << "No\n";
            return 0;
        }
        mf_add_branch(mf_source, mf_row(i), freq_x[i] / 3);
    }
    for (int i = 0; i < compressed_y_next; i++) {
        if (freq_y[i] % 3 != 0) {
            cout << "No\n";
            return 0;
        }
        mf_add_branch(mf_col(i), mf_well, freq_y[i] / 3);
    }
    for (int i = 0; i < n_points; i++) {
        mf_add_branch(mf_row(points[i].comp_x), mf_col(points[i].comp_y), 1);
    }

    if (mf_find() == n_points / 3) {
        cout << "Yes\n" << (n_points / 3) << "\n";
        // find the actual points
        for (int y = 0; y < compressed_y_next; y++) {
            int actual_y = uncompressed_ys[y];
            for (int x = 0; x < compressed_x_next; x++) {
                // if there's a +1 flow there's a colored dot
                if (mf_adj_mat[mf_col(y)][mf_row(x)]) {
                    int actual_x = uncompressed_xs[x];
                    cout << actual_x << " " << actual_y << "\n";
                }
            }
        }
    } else {
        cout << "No\n";
    }
	return 0;
}
