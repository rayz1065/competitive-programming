#include <bits/stdc++.h>

#define MAXN 1005
using namespace std;

// input data
int n_rows, m_cols;
vector<string> slashes;
// vector<int> graph[MAXN * MAXN * 4];
int colors[MAXN * MAXN * 4];

enum TileDire {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

TileDire itn[2][4] = {
    { // slash
        LEFT, DOWN, RIGHT, UP
    },
    { // backslash
        RIGHT, UP, LEFT, DOWN
    }
};
int delta_r[4] = { -1, 0, 1, 0 };
int delta_c[4] = { 0, 1, 0, -1 };

TileDire neighbor_dire (TileDire dire) {
    return (TileDire) ((dire + 2) % 4);
}

TileDire in_tile_neighbor (TileDire dire, bool is_backslash) {
    return itn[is_backslash][dire];
}

int encode_tile (int r, int c, TileDire dire) {
    return (r * m_cols + c) * 4 + dire;
}

void dfs_cc (int r, int c, TileDire dire, int color) {
    if (r < 0 || r >= n_rows || c < 0 || c >= m_cols) {
        return ;
    }
    int node = encode_tile(r, c, dire);
    if (colors[node] != -1) {
        return ;
    }
    colors[node] = color;
    // color neighbor in same tile
    TileDire in_tile_neigh_dire = in_tile_neighbor(dire, slashes[r][c] == '\\');
    dfs_cc(r, c, in_tile_neigh_dire, color);

    // color the neighbor tile
    TileDire neigh_dire = neighbor_dire(dire);
    int neigh_r = r + delta_r[dire];
    int neigh_c = c + delta_c[dire];
    dfs_cc(neigh_r, neigh_c, neigh_dire, color);
}

int count_cc () {
    fill(colors, colors + n_rows * m_cols * 4, -1);
    int cc = 0;
    for (int r = 0; r < n_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            for (int dire = 0; dire < 4; dire ++) {
                int node = encode_tile(r, c, (TileDire) dire);
                if (colors[node] == -1) {
                    dfs_cc(r, c, (TileDire) dire, cc++);
                }
            }
        }
    }
    return cc;
}

int main () {
    cin >> n_rows >> m_cols;
    slashes.resize(n_rows);
    for (int r = 0; r < n_rows; r++) {
        cin >> slashes[r];
    }

    // connected components

    cout << count_cc() << endl; // print the result
    return 0;
}
