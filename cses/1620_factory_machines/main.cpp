#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, target;
int machines[MAXN];

bool produces_enough(ll t) {
    ll res = 0;
    for (int i = 0; i < n && res <= target; i++) {
        res += t / machines[i];
    }
    return res >= target;
}

ll solve() {
    ll l = 0, r = LLONG_MAX >> 1, s = -1;

    while (l <= r) {
        ll m = (l + r) >> 1;
        if (produces_enough(m)) {
            s = m, r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return s;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> machines[i];
    }

    cout << solve() << "\n";
}
