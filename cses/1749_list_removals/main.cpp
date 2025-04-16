#include <bits/stdc++.h>
#define MAXN 200005
#define ST_ROOT 1
#define ST_LEFT(x) ((x) << 1)
#define ST_RIGHT(x) (((x) << 1) + 1)

using namespace std;

struct StNode {
    int value;
    int remaining;
} st[MAXN * 4];
int values[MAXN];

void st_init(int node, int l, int r) {
    if (l == r) {
        st[node].remaining = 1;
        return;
    }
    int m = (l + r) >> 1;
    st_init(ST_LEFT(node), l, m);
    st_init(ST_RIGHT(node), m + 1, r);
    st[node].remaining = r - l + 1;
}

int st_index(int node, int l, int r, int i) {
    if (l == r) {
        return l;
    }

    int m = (l + r) >> 1;
    int remaining_left = st[ST_LEFT(node)].remaining;
    if (remaining_left > i) {
        return st_index(ST_LEFT(node), l, m, i);
    }
    return st_index(ST_RIGHT(node), m + 1, r, i - remaining_left);
}

void st_delete(int node, int l, int r, int i) {
    if (l > i || r < i) {
        return;
    } else if (l == i && r == i) {
        st[node].remaining = 0;
        return;
    }

    int m = (l + r) >> 1;
    if (i <= m) {
        st_delete(ST_LEFT(node), l, m, i);
    } else {
        st_delete(ST_RIGHT(node), m + 1, r, i);
    }
    st[node].remaining =
        st[ST_LEFT(node)].remaining + st[ST_RIGHT(node)].remaining;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    st_init(ST_ROOT, 0, n - 1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int idx = st_index(ST_ROOT, 0, n - 1, x - 1);
        cout << values[idx] << " \n"[i + 1 == n];
        st_delete(ST_ROOT, 0, n - 1, idx);
    }
}
