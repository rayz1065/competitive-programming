#include <bits/stdc++.h>

#define ST_SIZE (200005 * 4)

using namespace std;

int n;
int st[ST_SIZE];

int st_set(int node, int l, int r, int i, int value) {
    if (r < i || l > i) {
        return st[node];
    }
    if (l == r) {
        return st[node] = value;
    }
    int m = (l + r) >> 1;
    return st[node] = max(st_set(node << 1, l, m, i, value),
                          st_set((node << 1) + 1, m + 1, r, i, value));
}

int st_get(int node, int l, int r, int target_l, int target_r) {
    if (r < target_l || l > target_r) {
        return INT_MIN >> 1;
    }
    if (target_l <= l && r <= target_r) {
        return st[node];
    }
    int m = (l + r) >> 1;
    return max(st_get(node << 1, l, m, target_l, target_r),
               st_get((node << 1) + 1, m + 1, r, target_l, target_r));
}

void inizia(int n, vector<int> values) {
    ::n = n;
    for (int i = 0; i < n; i++) {
        st_set(1, 0, n - 1, i, values[i]);
    }
}

void aggiorna(int i, int value) { st_set(1, 0, n - 1, i, value); }

int massimo(int left, int right) { return st_get(1, 0, n - 1, left, right); }
