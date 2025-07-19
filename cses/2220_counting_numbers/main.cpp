#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll _count_solutions(ll pw, ll maxv, int prev) {
    if (pw == 0) {
        return 1;
    }
    ll res = 0;
    ll base = _count_solutions(pw / 10, pw - 1, 1);
    for (int i = 0; i * pw <= maxv; i++) {
        if (i == prev) {
            continue;
        } else if ((i + 1) * pw > maxv) {
            res += _count_solutions(pw / 10, maxv - i * pw, i);
        } else {
            res += base;
        }
    }
    return res;
}

ll count_solutions(ll maxv) {
    if (maxv < 0) {
        return 0;
    }

    ll res = 1, pw = 1;
    for (; pw * 10 - 1 < maxv; pw = pw * 10) {
        res += _count_solutions(pw, pw * 10 - 1, 0);
    }
    res += _count_solutions(pw, maxv, 0);
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll a, b;
    cin >> a >> b;

    ll a_solutions = count_solutions(a - 1);
    ll b_solutions = count_solutions(b);

    cout << b_solutions - a_solutions << "\n";
}
