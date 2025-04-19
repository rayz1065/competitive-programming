#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef pair<int, int> pii;

vector<int> graph[MAXN];
int parent[MAXN];

int ufds_parent(int v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = ufds_parent(parent[v]);
}

void ufds_merge(int u, int v) {
    u = ufds_parent(u);
    v = ufds_parent(v);

    parent[u] = v;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        u = ufds_parent(u);
        v = ufds_parent(v);
        if (u != v) {
            ufds_merge(u, v);
            cerr << "removed " << u << ',' << v << "\n";
        }
    }

    vector<pii> res;
    for (int i = 0; i < n - 1; i++) {
        int u = i, v = i + 1;
        if (ufds_parent(u) != ufds_parent(v)) {
            ufds_merge(u, v);
            res.push_back({u, v});
        }
    }

    cout << res.size() << "\n";
    for (auto i : res) {
        cout << i.first + 1 << " " << i.second + 1 << "\n";
    }
}
