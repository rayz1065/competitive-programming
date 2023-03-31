#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
int numbers[MAXN];

void change_val (int a, int b) {
    numbers[a] = b;
}

ll panama (int l, int r) {
    ll s = 0;
    for (int i = 0; l + i <= r; i++) {
        int sgn = (i & 1) ? -1 : +1;
        s += sgn * numbers[i + l];
    }
    return s;
}

struct PanamaInfo {
    ll max_l;
    ll max_r;
    ll max_mid;
    ll sum;
};

PanamaInfo fast_panama (int l, int r, bool odd_start) {
    if (l == r) {
        int num = numbers[l];
        if (odd_start == (l & 1)) { // positive
            return { num, num, num, num };
        } else { // negative
            return { 0, 0, 0, -num };
        }
    }
    int m = (l + r) >> 1;
    PanamaInfo pl = fast_panama(l, m, odd_start);
    PanamaInfo pr = fast_panama(m + 1, r, odd_start);
    return {
        max(pl.max_l, pl.sum + pr.max_l),
        max(pr.max_r, pr.sum + pl.max_r),
        max(max(pl.max_mid, pr.max_mid), pl.max_r + pr.max_l),
        pl.sum + pr.sum,
    };
}

ll max_panama (int l, int r) {
    PanamaInfo odds = fast_panama(l, r, true);
    PanamaInfo evens = fast_panama(l, r, false);
    return max(odds.max_mid, evens.max_mid);
}

void init () {}

int main () {
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
            cerr << "chaging " << a << " to " << b << "\n";
            change_val(a, b);
        } else {
            a--, b--;
            cerr << "max_panama(" << a << ", " << b << ")\n";
            cout << max_panama(a, b) << "\n";
        }
    }
}
