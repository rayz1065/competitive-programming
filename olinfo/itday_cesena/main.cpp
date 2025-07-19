#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 200005

using namespace std;

int ufds_kiosks[MAXN];
int ufds_parent[MAXN];
int ufds_rank[MAXN];
vector<int> edges_by_weight[MAXN];

int ufds_get_parent(int u) {
    if (ufds_parent[u] == u) {
        return u;
    }
    return ufds_parent[u] = ufds_get_parent(ufds_parent[u]);
}

void ufds_merge(int u, int v) {
    u = ufds_get_parent(u), v = ufds_get_parent(v);
    if (u == v) {
        return;
    }
    if (ufds_rank[u] < ufds_rank[v]) {
        swap(u, v);
    }
    ufds_kiosks[u] += ufds_kiosks[v];
    ufds_parent[v] = u;
    ufds_rank[u] += ufds_rank[u] == ufds_rank[v];
}

int visita(int n, int m, int k, vector<int> kiosk, vector<int> street_a,
           vector<int> street_b, vector<int> street_t) {
    for (int i = 0; i < n; i++) {
        ufds_parent[i] = i;
        ufds_rank[i] = 0;
    }
    for (auto i : kiosk) {
        ufds_kiosks[i] += 1;
    }
    for (int i = 0; i < m; i++) {
        edges_by_weight[street_t[i]].push_back(i);
    }

    int res = 0;
    for (int t = k; t > 0; t--) {
        for (auto j : edges_by_weight[t]) {
            ufds_merge(street_a[j], street_b[j]);
        }
        int zero_parent = ufds_get_parent(0);
        if (ufds_kiosks[zero_parent] > 0) {
            ufds_kiosks[zero_parent] -= 1;
            res += 1;
        }
    }

    return res;
}
