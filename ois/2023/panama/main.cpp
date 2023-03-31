#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
int numbers[MAXN];

// ll panama (int l, int r) {
//     ll s = 0;
//     for (int i = 0; l + i <= r; i++) {
//         int sgn = (i & 1) ? -1 : +1;
//         s += sgn * numbers[i + l];
//     }
//     return s;
// }

struct PanamaInfo {
    ll max_l;
    ll max_r;
    ll max_mid;
    ll sum;
};
PanamaInfo st[2][MAXN * 4];

PanamaInfo panama_one (int pos, int num, bool odd_start) {
    if (odd_start == (pos & 1)) { // positive
        return { num, num, num, num };
    } else { // negative
        return { 0, 0, 0, -num };
    }
}

PanamaInfo panama_comb (PanamaInfo pl, PanamaInfo pr) {
    return {
        max(pl.max_l, pl.sum + pr.max_l),
        max(pr.max_r, pr.sum + pl.max_r),
        max(max(pl.max_mid, pr.max_mid), pl.max_r + pr.max_l),
        pl.sum + pr.sum,
    };
}

// PanamaInfo fast_panama (int l, int r, bool odd_start) {
//     if (l == r) {
//         int num = numbers[l];
//         if (odd_start == (l & 1)) { // positive
//             return { num, num, num, num };
//         } else { // negative
//             return { 0, 0, 0, -num };
//         }
//     }
//     int m = (l + r) >> 1;
//     PanamaInfo pl = fast_panama(l, m, odd_start);
//     PanamaInfo pr = fast_panama(m + 1, r, odd_start);
//     return {
//         max(pl.max_l, pl.sum + pr.max_l),
//         max(pr.max_r, pr.sum + pl.max_r),
//         max(max(pl.max_mid, pr.max_mid), pl.max_r + pr.max_l),
//         pl.sum + pr.sum,
//     };
// }

void st_update (int node, int node_l, int node_r, int x, int new_val, bool odds) {
    if (node_r < x || node_l > x) return ;
    if (node_l == node_r) {
        st[odds][node] = panama_one(node_l, new_val, odds);
        return ;
    }
    int m = (node_l + node_r) >> 1;
    st_update(node << 1, node_l, m, x, new_val, odds);
    st_update(node << 1 | 1, m + 1, node_r, x, new_val, odds);
    st[odds][node] = panama_comb(st[odds][node << 1], st[odds][node << 1 | 1]);
}

ll st_sum (int node, int node_l, int node_r, int l, int r, bool odds) {
    if (node_r < l || node_l > r) return 0ll;
    if (node_l >= l && node_r <= r) {
        return st[odds][node].sum;
    }
    int m = (node_l + node_r) >> 1;
    return st_sum(node << 1, node_l, m, l, r, odds) + \
           st_sum(node << 1 | 1, m + 1, node_r, l, r, odds);
}

PanamaInfo st_panama (int node, int node_l, int node_r, int l, int r, bool odds) {
    if (node_r < l || node_l > r) return { 0, 0, 0, 0 };
    if (node_l >= l && node_r <= r) {
        return st[odds][node];
    }
    int m = (node_l + node_r) >> 1;
    PanamaInfo pl = st_panama(node << 1, node_l, m, l, r, odds);
    PanamaInfo pr = st_panama(node << 1 | 1, m + 1, node_r, l, r, odds);
    return panama_comb(pl, pr);
}

ll max_panama (int l, int r) {
    // PanamaInfo odds = fast_panama(l, r, true);
    // PanamaInfo evens = fast_panama(l, r, false);
    PanamaInfo st_odds = st_panama(1, 0, n - 1, l, r, true);
    PanamaInfo st_evens = st_panama(1, 0, n - 1, l, r, false);
    // assert (st_odds.max_mid == odds.max_mid);
    // assert (st_evens.max_mid == evens.max_mid);
    return max(st_odds.max_mid, st_evens.max_mid);
}

void change_val (int a, int b) {
    numbers[a] = b;
    st_update(1, 0, n - 1, a, b, 0);
    st_update(1, 0, n - 1, a, b, 1);
    // for (int j = 0; j < n; j++) {
    //     cerr << st_sum(1, 0, n - 1, j, j, 0) << " \n"[j + 1 == n];
    // }
    // for (int j = 0; j < n; j++) {
    //     cerr << st_sum(1, 0, n - 1, j, j, 1) << " \n"[j + 1 == n];
    // }
}

void init () {
    for (int i = 0; i < n; i++) {
        st_update(1, 0, n - 1, i, numbers[i], 0);
        st_update(1, 0, n - 1, i, numbers[i], 1);
    }
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    init();
    for (int i = 0; i < q; i++) {
        int qtype, a, b;
        cin >> qtype >> a >> b;
        if (qtype == 1) {
            a--;
            // cerr << "chaging " << a << " to " << b << "\n";
            change_val(a, b);
        } else {
            a--, b--;
            // cerr << "max_panama(" << a << ", " << b << ")\n";
            cout << max_panama(a, b) << "\n";
        }
    }
}
