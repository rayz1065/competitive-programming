#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1050000

using namespace std;

struct StNode {
    long long sum;
    long long min;
} st[MAXN * 2];
struct StLazy {
    bool lazy_reset;
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

inline int st_size (int i) {
    return 1 << (__builtin_clz(i) - st_h);
}

void st_apply_add (int node, long long x) {
    if (node < n_nodes) {
        st_lazy[node].lazy_add += x;
    }
    st[node].sum += x * st_size(node);
    st[node].min += x;
}

void st_apply_set (int node, long long x) {
    if (node < n_nodes) {
        st_lazy[node].lazy_add = x;
        st_lazy[node].lazy_reset = true;
    }
    st[node].sum = x * st_size(node);
    st[node].min = x;
}

void st_lazy_prop (int node) {
    if (st_lazy[node].lazy_reset) {
        st_apply_set(node << 1, st_lazy[node].lazy_add);
        st_apply_set(node << 1 | 1, st_lazy[node].lazy_add);
        st_lazy[node].lazy_reset = false;
        st_lazy[node].lazy_add = 0;
    } else if (st_lazy[node].lazy_add) {
        st_apply_add(node << 1, st_lazy[node].lazy_add);
        st_apply_add(node << 1 | 1, st_lazy[node].lazy_add);
        st_lazy[node].lazy_add = 0;
    }
}

void st_build (int i) {
    i >>= 1;
    while (i > 0) {
        st[i].min = (st_lazy[i].lazy_reset ? 0 : min(st[i << 1].min, st[i << 1 | 1].min)) + st_lazy[i].lazy_add;
        st[i].sum = (st_lazy[i].lazy_reset ? 0 : st[i << 1].sum + st[i << 1 | 1].sum) + st_lazy[i].lazy_add * st_size(i);
        i >>= 1;
    }
}

void st_lazy_prop_2 (int p) {
    for (int i = 32 - st_h; i >= 0; i--) {
        int node = (p >> i);
        st_lazy_prop(node);
    }
}

void st_set (int l, int r, long long x) {
    l += n_nodes;
    r += n_nodes;
    st_lazy_prop_2(l);
    st_lazy_prop_2(r - 1);
    int l0 = l, r0 = r;
    while (l < r) {
        if (l & 1) {
            st_apply_set(l++, x);
        }
        if (r & 1) {
            st_apply_set(--r, x);
        }
        l >>= 1, r >>= 1;
    }
    st_build(l0);
    st_build(r0 - 1);
}

void st_add (int l, int r, long long x) {
    l += n_nodes;
    r += n_nodes;
    st_lazy_prop_2(l);
    st_lazy_prop_2(r - 1);
    int l0 = l, r0 = r;
    while (l < r) {
        if (l & 1) {
            st_apply_add(l++, x);
        }
        if (r & 1) {
            st_apply_add(--r, x);
        }
        l >>= 1, r >>= 1;
    }
    st_build(l0);
    st_build(r0 - 1);
}

long long st_sum (int l, int r) {
    l += n_nodes;
    r += n_nodes;
    st_lazy_prop_2(l);
    st_lazy_prop_2(r - 1);
    long long s = 0;
    while (l < r) {
        if (l & 1) {
            s += st[l++].sum;
        }
        if (r & 1) {
            s += st[--r].sum;
        }
        l >>= 1, r >>= 1;
    }
    return s;
}

long long st_min (int l, int r) {
    l += n_nodes;
    r += n_nodes;
    st_lazy_prop_2(l);
    st_lazy_prop_2(r - 1);
    long long s = LLONG_MAX;
    while (l < r) {
        if (l & 1) {
            s = min(s, st[l++].min);
        }
        if (r & 1) {
            s = min(s, st[--r].min);
        }
        l >>= 1, r >>= 1;
    }
    return s;
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
        cout << st_sum(i, i + 1) << " \n"[i == r];
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
    return st_sum(l, r);
}

void add(int l, int r, long long x) {
    st_add(l, r, x);
#ifdef DEBUG
    printf("Adding %d to range [%d, %d]\n", x, l, r - 1);
    st_debug(0, n_nodes - 1);
#endif
}

void set_range(int l, int r, long long x) {
    // st_set(st_root, l, r - 1, x);
    st_set(l, r, x);
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
    return st_min(l, r);
}

int lower_bound(int l, int r, long long x) {
#ifdef DEBUG
    printf("Getting lb of %d in range [%d, %d]\n", x, l, r - 1);
    // st_debug(l, r - 1);
#endif
    return st_lb(st_root, l, r - 1, x);
}
