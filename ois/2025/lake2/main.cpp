#include <bits/stdc++.h>
#define MAXN 1005
#define MAXQ 200005
#define ST_SIZE (1 << 24)
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)
#define ST_ROOT 1

using namespace std;

int n, m;
int solutions[MAXQ];
struct {
    int r1, r2, c1, c2;
} queries[MAXQ];

enum LazyFlag { LAZY_NONE, LAZY_TOGGLE, LAZY_RESET, LAZY_SET };

struct SegmentTreeNode {
    LazyFlag lazy_flag;
    int sum;
} st[ST_SIZE];

void _st_toggle(int node, int l, int r, int tl, int tr);
void _st_lazy(int node, int l, int r);
void _st_reset(int node, int l, int r);
void _st_set(int node, int l, int r);

void _st_lazy(int node, int l, int r) {
    if (st[node].lazy_flag == LAZY_NONE || l == r) return;
    auto lazy = st[node].lazy_flag;
    st[node].lazy_flag = LAZY_NONE;
    int m = (l + r) / 2;
    if (lazy == LAZY_TOGGLE) {
        _st_toggle(ST_LEFT(node), l, m, l, r);
        _st_toggle(ST_RIGHT(node), m + 1, r, l, r);
    } else if (lazy == LAZY_RESET) {
        _st_reset(ST_LEFT(node), l, m);
        _st_reset(ST_RIGHT(node), m + 1, r);
    } else if (lazy == LAZY_SET) {
        _st_set(ST_LEFT(node), l, m);
        _st_set(ST_RIGHT(node), m + 1, r);
    }
}

void _st_toggle(int node, int l, int r, int tl, int tr) {
    if (l > tr || r < tl) return;
    if (tl <= l && r <= tr) {
        int sz = r - l + 1;
        st[node].sum = sz - st[node].sum;

        if (st[node].lazy_flag == LAZY_TOGGLE) {
            st[node].lazy_flag = LAZY_NONE;
        } else if (st[node].lazy_flag == LAZY_RESET) {
            st[node].lazy_flag = LAZY_SET;
        } else if (st[node].lazy_flag == LAZY_SET) {
            st[node].lazy_flag = LAZY_RESET;
        } else {
            st[node].lazy_flag = LAZY_TOGGLE;
        }
        return;
    }
    _st_lazy(node, l, r);
    int m = (l + r) / 2;
    _st_toggle(ST_LEFT(node), l, m, tl, tr);
    _st_toggle(ST_RIGHT(node), m + 1, r, tl, tr);
    st[node].sum = st[ST_LEFT(node)].sum + st[ST_RIGHT(node)].sum;
}

int _st_query(int node, int l, int r, int tl, int tr) {
    if (l > tr || r < tl) return 0;
    _st_lazy(node, l, r);
    if (tl <= l && r <= tr) {
        return st[node].sum;
    }
    int m = (l + r) / 2;
    return (_st_query(ST_LEFT(node), l, m, tl, tr) +
            _st_query(ST_RIGHT(node), m + 1, r, tl, tr));
}

void _st_reset(int node, int l, int r) {
    st[node].sum = 0;
    st[node].lazy_flag = LAZY_RESET;
}

void _st_set(int node, int l, int r) {
    st[node].sum = r - l + 1;
    st[node].lazy_flag = LAZY_SET;
}

void st_toggle(int l, int r) { _st_toggle(ST_ROOT, 0, max(n, m), l, r); }
void st_reset() { _st_reset(ST_ROOT, 0, 0); }
int st_query(int l, int r) { return _st_query(ST_ROOT, 0, max(n, m), l, r); }

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

void fastout(int x) {
    int rev = 0;
    do {
        rev = rev * 11 + (x % 10) + 1;
        x /= 10;
    } while (x);
    while (rev) {
        putchar_unlocked(rev % 11 + '0' - 1);
        rev /= 11;
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int q;
    n = fastin(), m = fastin(), q = fastin();
    n += 2, m += 2;  // perimeter around

    vector<pair<int, int>> r_times(q * 2), c_times(q * 2);

    for (int i = 0; i < q; i++) {
        queries[i] = {fastin(), fastin(), fastin(), fastin()};
        r_times[i * 2] = {queries[i].r1, i};
        r_times[i * 2 + 1] = {queries[i].r2 + 1, i};
        c_times[i * 2] = {queries[i].c1, i};
        c_times[i * 2 + 1] = {queries[i].c2 + 1, i};
    }

    sort(r_times.begin(), r_times.end());
    sort(c_times.begin(), c_times.end());

    for (int i = 0; i < 2 * q;) {
        int curr_r = r_times[i].first;
        int prev = 0;
        for (; i < 2 * q && r_times[i].first == curr_r; i++) {
            int t = r_times[i].second;
            st_toggle(queries[t].c1, queries[t].c2);
            solutions[t] += st[ST_ROOT].sum - prev;
            prev = st[ST_ROOT].sum;
        }
        st_reset();
    }

    for (int i = 0; i < 2 * q;) {
        int curr_c = c_times[i].first;
        int prev = 0;
        for (; i < 2 * q && c_times[i].first == curr_c; i++) {
            int t = c_times[i].second;
            st_toggle(queries[t].r1, queries[t].r2);
            solutions[t] += st[ST_ROOT].sum - prev;
            prev = st[ST_ROOT].sum;
        }
        st_reset();
    }

    int res = 0;
    for (int i = 0; i < q; i++) {
        res += solutions[i];
        fastout(res);
        putchar_unlocked('\n');
    }
}
