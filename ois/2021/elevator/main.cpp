#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 201000

using namespace std;

struct StNode {
    // int am;
    int max;
    int lazy_add;
};

StNode st[MAXN * 4];
int stops[MAXN];
int n_nodes, stops_count;
void st_add (int node, int node_l, int node_r, int l, int r, int am);

void st_recalc (int node) {
    // st[node].am = st[node << 1].am + st[node << 1 | 1].am;
    st[node].max = max(st[node << 1].max, st[node << 1 | 1].max);
}

void st_lazy (int node, int node_l, int node_r) {
    if (!st[node].lazy_add) return ;
    int mid = (node_l + node_r) >> 1;
    st_add(node << 1, node_l, mid, 0, MAXN, st[node].lazy_add);
    st_add(node << 1 | 1, mid + 1, node_r, 0, MAXN, st[node].lazy_add);
    st[node].lazy_add = 0;
}

void st_add (int node, int node_l, int node_r, int l, int r, int am) {
    if (node_l > r || node_r < l) return ;
    if (l <= node_l && node_r <= r) {
        if (node_l != node_r) st[node].lazy_add += am;
        // st[node].am += am * (node_r - node_l + 1);
        st[node].max += am;
        return ;
    }
    st_lazy(node, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    st_add(node << 1, node_l, mid, l, r, am);
    st_add(node << 1 | 1, mid + 1, node_r, l, r, am);
    st_recalc(node);
}

int st_max (int node, int node_l, int node_r, int l, int r) {
    if (node_l > r || node_r < l) return -1;
    if (l <= node_l && node_r <= r) {
        return st[node].max;
    }
    st_lazy(node, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    return max(st_max(node << 1, node_l, mid, l, r),
               st_max(node << 1 | 1, mid + 1, node_r, l, r));
}

// index of first max
int st_f_max (int node, int node_l, int node_r) {
    if (node_l == node_r) {
        return node_l;
    }
    st_lazy(node, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    if (st[node << 1].max == st[node].max) {
        return st_f_max(node << 1, node_l, mid);
    }
    return st_f_max(node << 1 | 1, mid + 1, node_r);
}

void add_trip (int a, int b, int am, bool is_first) {
    int dire = a < b ? +1 : -1;
    if (!is_first) a += dire;
    if (a > b) swap(a, b);
    // cout << "[" << a << ", " << b << "] += " << am << "\n";
    // for (int j = 0; j < 10; j++) {
    //     cout << st_max(1, 0, n_nodes - 1, j, j) << " \n"[j + 1 == 10];
    // }
    st_add(1, 0, n_nodes - 1, a, b, am);
    // for (int j = 0; j < 10; j++) {
    //     cout << st_max(1, 0, n_nodes - 1, j, j) << " \n"[j + 1 == 10];
    // }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int q_queries;
    n_nodes = 200001;
    cin >> stops_count;
    for (int i = 0; i < stops_count; i++) {
        cin >> stops[i];
        if (i > 0) {
            add_trip(stops[i - 1], stops[i], 1, i == 1);
        }
    }
    cin >> q_queries;
    for (int i = 0; i < q_queries; i++) {
        int stop_idx, new_stop;
        cin >> stop_idx >> new_stop;
        if (stop_idx > 0) {
            // cout << "removing for " << stop_idx << ", [" << stops[stop_idx - 1] << " " << stops[stop_idx] << "]\n";
            // cout << "adding " << " [" << stops[stop_idx - 1] << " " << new_stop << "]\n";
            add_trip(stops[stop_idx - 1], stops[stop_idx], -1, stop_idx == 1);
            add_trip(stops[stop_idx - 1], new_stop, +1, stop_idx == 1);
        }
        if (stop_idx + 1 < stops_count) {
            // cout << "removing for " << stop_idx << ", [" << stops[stop_idx] << " " << stops[stop_idx + 1] << "]\n";
            // cout << "adding " << " [" << new_stop << " " << stops[stop_idx + 1] << "]\n";
            add_trip(stops[stop_idx], stops[stop_idx + 1], -1, stop_idx == 0);
            add_trip(new_stop, stops[stop_idx + 1], +1, stop_idx == 0);
        }
        stops[stop_idx] = new_stop;
        cout << st_f_max(1, 0, n_nodes - 1) << " " << st[1].max << "\n";
    }
}
