#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int heights[MAXN];
int st[MAXN * 4];

void st_update (int node, int node_l, int node_r, int x, int v) {
    if (node_l > x || node_r < x) return ;
    if (node_l == node_r) {
        st[node] = v;
        return ;
    }
    int m = (node_l + node_r) >> 1;
    st_update(node<<1, node_l, m, x, v);
    st_update(node<<1|1, m + 1, node_r, x, v);
    st[node] = max(st[node<<1], st[node<<1|1]);
}

int st_first_gt (int node, int node_l, int node_r, int x, int v) {
    if (node_l > x) return -1;
    if (st[node] <= v) return -1; // all shorter
    if (node_l == node_r) {
        return node_l;
    }
    int m = (node_l + node_r) >> 1;
    int r_res = st_first_gt(node<<1|1, m + 1, node_r, x, v);
    if (r_res != -1) return r_res;
    return st_first_gt(node<<1, node_l, m, x, v);
}

int st_next_gt (int node, int node_l, int node_r, int x, int v) {
    if (node_r < x) return -1;
    if (st[node] <= v) return -1; // all shorter
    if (node_l == node_r) {
        return node_l;
    }
    int m = (node_l + node_r) >> 1;
    int l_res = st_next_gt(node<<1, node_l, m, x, v);
    if (l_res != -1) return l_res;
    return st_next_gt(node<<1|1, m + 1, node_r, x, v);
}

pair<int, int> chiedi(int x) {
    int l = st_first_gt(1, 0, n - 1, x, heights[x]);
    l = max(l, 0);
    int r = st_next_gt(1, 0, n - 1, x, heights[x]);
    if (r == -1) r = n - 1;
    return { l, r };
}

void cambia(int x, int h) {
    heights[x] = h;
    st_update(1, 0, n - 1, x, h);
}

void inizializza(int N, vector<int> H) {
    n = N;
    for (int i = 0; i < n; i++) {
        heights[i] = H[i];
        st_update(1, 0, n - 1, i, heights[i]);
    }
}
