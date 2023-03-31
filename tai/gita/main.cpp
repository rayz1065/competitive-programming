#include <bits/stdc++.h>
#define MAXN 1050000

using namespace std;

int n_cities, st_nodes;
int st[MAXN * 2];
int cap[MAXN];
vector<int> graph[MAXN];
bool visited[MAXN];

int sweetness[MAXN]; // compressed sweetness of city[i]
int original_sweetness[MAXN]; // maps compressed index to original
pair<int, int> mapping[MAXN]; // used for index compression

void st_build (int i) {
    for (i >>= 1; i > 0; i >>= 1) {
        st[i] = st[i << 1] + st[i << 1 | 1];
    }
}

void st_set (int i, int v) {
    i += st_nodes;
    st[i] = v;
    st_build(i);
}

int st_sum_lb (int x) {
    int node = 1;
    while (node < st_nodes) {
        if (st[node << 1] >= x) {
            node <<= 1;
        } else {
            x -= st[node << 1];
            node = node << 1 | 1;
        }
    }
    return node - st_nodes;
}

int dfs (int node, bool maximize_sweet) {
    visited[node] = true;
    st_set(sweetness[node], 1);
    int min_found = INT_MAX >> 1;
    int max_found = -1;
    for (auto j: graph[node]) {
        if (!visited[j]) {
            int adj_sw = dfs(j, !maximize_sweet);
            min_found = min(min_found, adj_sw);
            max_found = max(max_found, adj_sw);
        }
    }
    if (max_found == -1) {
        // no neighbors
        min_found = max_found = st_sum_lb(cap[node] + 1);
    }
    st_set(sweetness[node], 0);
    return maximize_sweet ? max_found : min_found;
}

bool cmp_sweet (int i, int j) {
    return original_sweetness[i] < original_sweetness[j];
}

void index_compress (vector<int> &dolcezza) {
    for (int i = 0; i < n_cities; i++) {
        mapping[i] = { dolcezza[i], i };
    }
    sort(mapping, mapping + n_cities);
    for (int i = 0; i < n_cities; i++) {
        original_sweetness[i] = mapping[i].first;
        sweetness[mapping[i].second] = i;
    }
}

int visita(int N, vector<int> &A, vector<int> &B, vector<int> &dolcezza, vector<int> &C) {
    ::n_cities = N;
    for (int i = 0; i < n_cities - 1; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    for (int i = 0; i < n_cities; i++) {
        cap[i] = C[i];
    }
    index_compress(dolcezza);
    st_nodes = 1 << (8 * sizeof(int) - __builtin_clz(n_cities));
    return original_sweetness[dfs(0, true)];
}
