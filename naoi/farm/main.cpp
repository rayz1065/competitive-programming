#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_map<ll, int> pens;
multiset<int> pen_sizes;

ll get_pen_id(ll n, ll m, ll r, ll c) {
    if (n < m) {
        swap(n, m);
        swap(r, c);
    }
    // vertical rectangle
    ll remainder = n % m;
    ll inc = r / m;
    if (r < n - remainder) {
        // before remainder
        return inc;
    }
    return get_pen_id(remainder, m, r - inc * m, c) + inc;
}

void move_cow(ll pen_id, int delta) {
    if (pens.find(pen_id) != pens.end()) {
        pen_sizes.erase(pen_sizes.find(pens[pen_id]));
    }
    pens[pen_id] += delta;
    pen_sizes.insert(pens[pen_id]);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n, m;
    int q;
    cin >> n >> m >> q;

    while (q--) {
        char op;
        ll r, c;
        cin >> op;

        if (op == 'c') {
            int res = pen_sizes.empty() ? 0 : *pen_sizes.rbegin();
            cout << res << "\n";
            continue;
        }

        cin >> r >> c;
        ll pen_id = get_pen_id(n, m, r, c);
        move_cow(pen_id, op == 'a' ? 1 : -1);
    }
}
