#include <bits/stdc++.h>
#define MAXN 200005
#define MOD 1000000007

using namespace std;

int rows, cols, n;
int positions[MAXN][2];
int ufds_parent[MAXN];
int ufds_rank[MAXN];
unordered_map<int, int> row_parent;
unordered_map<int, int> col_parent;
unordered_map<int, int> diagonal1_parent;
unordered_map<int, int> diagonal2_parent;
int connected_components;

void ufds_init() {
    for (int i = 0; i < n; i++) {
        ufds_parent[i] = i;
        ufds_rank[i] = 0;
    }
    connected_components = n;
}

int ufds_find(int a) {
    if (ufds_parent[a] == a) {
        return a;
    }
    return ufds_parent[a] = ufds_find(ufds_parent[a]);
}

void ufds_merge(int a, int b) {
    a = ufds_find(a), b = ufds_find(b);
    if (a == b) {
        return ;
    }
    connected_components--;

    if (ufds_rank[a] < ufds_rank[b]) {
        ufds_parent[a] = b;
    } else if (ufds_rank[a] > ufds_rank[b]) {
        ufds_parent[b] = a;
    } else {
        ufds_parent[a] = b;
        ufds_rank[b] += 1;
    }
}

void parent_merge(int i, int location,
                  unordered_map<int, int> &location_parent) {
    auto location_p = location_parent.find(location);
    if (location_p == location_parent.end()) {
        location_parent[location] = i;
        return;
    }

    ufds_merge(i, location_parent[location]);
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> rows >> cols >> n;

    for (int i = 0; i < n; i++) {
        cin >> positions[i][0] >> positions[i][1];
    }

    ufds_init();

    for (int i = 0; i < n; i++) {
        int row = positions[i][0];
        int col = positions[i][1];
        int diagonal1 = row - col;
        int diagonal2 = row + col;

        parent_merge(i, row, row_parent);
        parent_merge(i, col, col_parent);
        parent_merge(i, diagonal1, diagonal1_parent);
        parent_merge(i, diagonal2, diagonal2_parent);
    }

    int res = 1;
    for (int i = 0; i < connected_components; i++) {
        res = (res << 1) % MOD;
    }

    cout << res << "\n";
}
