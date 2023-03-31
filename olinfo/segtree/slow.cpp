#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1050000

using namespace std;

struct StNode {
    long long sum;
    long long min;
} st[MAXN * 2];
struct StLazy {
    bool apply_value;
    long long lazy_value;
    long long lazy_add;
} st_lazy[MAXN];
int st_root;
int n_nodes;
int st_h;

inline int st_node_l (int i) {
    int lz = __builtin_clz(i);
    return (i - (1 << (31 - lz))) << (lz - st_h);
}

inline int st_node_r (int i) {
    int lz = __builtin_clz(i);
    return ((i - (1 << (31 - lz)) + 1) << (lz - st_h)) - 1;
}

void st_set (int node, int l, int r, long long x);
void st_add (int node, int l, int r, long long x);

void st_lazy_prop (int node) {
    if (st_lazy[node].apply_value) {
        st_set(node << 1, 0, n_nodes - 1, st_lazy[node].lazy_value);
        st_set(node << 1 | 1, 0, n_nodes - 1, st_lazy[node].lazy_value);
    } else { // add
        st_add(node << 1, 0, n_nodes - 1, st_lazy[node].lazy_add);
        st_add(node << 1 | 1, 0, n_nodes - 1, st_lazy[node].lazy_add);
    }
    st_lazy[node].apply_value = false;
    st_lazy[node].lazy_add = 0;
    st_lazy[node].lazy_value = 0;
}

void st_set (int node, int l, int r, long long x) {
    int node_l = st_node_l(node), node_r = st_node_r(node);
    if (node_l > r || node_r < l) {
        return ;
    }
    if (l <= node_l && node_r <= r) {
        // fully contained
        if (node_l != node_r) {
            // setting overtakes addition
            st_lazy[node].lazy_value = x;
            st_lazy[node].apply_value = true;
            st_lazy[node].lazy_add = 0;
        }
        st[node].sum = x * (node_r - node_l + 1);
        st[node].min = x;
        return ;
    }
    // split and recalculate
    st_lazy_prop(node);
    st_set(node << 1, l, r, x);
    st_set(node << 1 | 1, l, r, x);
    st[node].sum = st[node << 1].sum + st[node << 1 | 1].sum;
    st[node].min = min(st[node << 1].min, st[node << 1 | 1].min);
}

void st_add (int node, int l, int r, long long x) {
    int node_l = st_node_l(node), node_r = st_node_r(node);
    if (node_l > r || node_r < l) {
        return ;
    }
    if (l <= node_l && node_r <= r) {
        // fully contained
        if (node_l != node_r) {
            if (st_lazy[node].apply_value) {
                st_lazy[node].lazy_value += x;
            } else {
                st_lazy[node].lazy_add += x;
            }
        }
        st[node].sum += x * (node_r - node_l + 1);
        st[node].min += x;
        return ;
    }
    // split and recalculate
    if (st_lazy[node].apply_value) {
        st_lazy_prop(node);
    }
    st_add(node << 1, l, r, x);
    st_add(node << 1 | 1, l, r, x);
    st[node].sum = st[node << 1].sum + st[node << 1 | 1].sum + st_lazy[node].lazy_add * (node_r - node_l + 1);
    st[node].min = min(st[node << 1].min, st[node << 1 | 1].min) + st_lazy[node].lazy_add;
}

long long st_sum (int node, int l, int r) {
    int node_l = st_node_l(node), node_r = st_node_r(node);
    if (node_l > r || node_r < l) {
        return 0;
    }
    if (l <= node_l && node_r <= r) {
        // fully contained
        return st[node].sum;
    }
    // split and recalculate
    st_lazy_prop(node);
    long long l_sum = (st_node_l(node << 1) > r || st_node_r(node << 1) < l) ? 0 : st_sum(node << 1, l, r);
    long long r_sum = (st_node_l(node << 1 | 1) > r || st_node_r(node << 1 | 1) < l) ? 0 : st_sum(node << 1 | 1, l, r);
    return l_sum + r_sum;
}

long long st_min (int node, int l, int r) {
    int node_l = st_node_l(node), node_r = st_node_r(node);
    if (node_l > r || node_r < l) {
        return LLONG_MAX;
    }
    if (l <= node_l && node_r <= r) {
        // fully contained
        return st[node].min;
    }
    // split and recalculate
    st_lazy_prop(node);
    long long l_min = st_min(node << 1, l, r);
    long long r_min = st_min(node << 1 | 1, l, r);
    return min(l_min, r_min);
}

long long st_lb (int node, int l, int r, long long x) {
    int node_l = st_node_l(node), node_r = st_node_r(node);
    if (node_l > r || node_r < l || st[node].min > x) {
        return -1;
    }
    if (node_l == node_r) {
        // found it
        return node_l;
    }
    // split and recalculate
    st_lazy_prop(node);
    long long l_res = st_lb(node << 1, l, r, x);
    if (l_res != -1) {
        return l_res;
    }
    return st_lb(node << 1 | 1, l, r, x);
}

void st_make (vector<long long> &values) {
    for (int i = 0; i < n_nodes; i++) {
        st[i + n_nodes].min = st[i + n_nodes].sum = values[i];
    }
    for (int i = n_nodes - 1; i >= 1; i--) {
        st[i].min = min(st[i << 1].min, st[i << 1 | 1].min);
        st[i].sum = st[i << 1].sum + st[i << 1 | 1].sum;
    }
}

#ifdef DEBUG
void st_debug (int l, int r) {
    for (int i = l; i <= r; i++) {
        cout << st_sum(st_root, 0, n_nodes - 1, i, i) << " \n"[i == r];
    }
}
#endif

void init(vector<long long> a) {
    st_root = 1;
    n_nodes = (1 << (32 - __builtin_clz(a.size() - 1)));
    st_h = __builtin_clz(n_nodes);
    a.resize(n_nodes, 0);
    st_make(a);
#ifdef DEBUG
    st_debug(0, n_nodes - 1);
#endif
}

long long get_sum(int l, int r) {
#ifdef DEBUG
    printf("Getting sum [%d, %d]\n", l, r - 1);
    // st_debug(l, r - 1);
#endif
    return st_sum(st_root, l, r - 1);
}

void add(int l, int r, long long x) {
    st_add(st_root, l, r - 1, x);
#ifdef DEBUG
    printf("Adding %d to range [%d, %d]\n", x, l, r - 1);
    st_debug(0, n_nodes - 1);
#endif
}

void set_range(int l, int r, long long x) {
    st_set(st_root, l, r - 1, x);
#ifdef DEBUG
    printf("Setting range [%d, %d] to %d\n", l, r - 1, x);
    st_debug(0, n_nodes - 1);
#endif
}

long long get_min(int l, int r) {
#ifdef DEBUG
    printf("Getting min from range [%d, %d]\n", l, r - 1);
    // st_debug(l, r - 1);
#endif
    return st_min(st_root, l, r - 1);
}

int lower_bound(int l, int r, long long x) {
#ifdef DEBUG
    printf("Getting lb of %d in range [%d, %d]\n", x, l, r - 1);
    // st_debug(l, r - 1);
#endif
    return st_lb(st_root, l, r - 1, x);
}
