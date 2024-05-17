#include <bits/stdc++.h>
#define MAXN 200000
#define LOGMAXK 30

using namespace std;

int n;
int up[MAXN][LOGMAXK];

void make_lca() {
    for (int j = 1; j < LOGMAXK; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

int traverse(int node, int k) {
    for (int j = LOGMAXK - 1; j >= 0; j--) {
        while ((k - (1 << j)) >= 0) {
            k -= (1 << j);
            node = up[node][j];
        }
    }

    return node;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> up[i][0];
        up[i][0]--;
    }

    make_lca();

    while (q--) {
        int node, k;
        cin >> node >> k;
        node--;
        cout << traverse(node, k) + 1 << "\n";
    }
}
