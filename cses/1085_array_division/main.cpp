#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, k, values[MAXN];

bool check(ll target) {
    ll curr = 0;
    int used = 0;
    for (int i = 0; i < n; i++) {
        if (curr + values[i] <= target) {
            curr += values[i];
        } else {
            curr = values[i];
            used += 1;
        }
    }

    used += curr > 0;
    return used <= k;
}

ll solve() {
    ll l = *max_element(values, values + n), r = LLONG_MAX >> 1, s = -1;

    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (check(m)) {
            r = m - 1, s = m;
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

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << solve() << "\n";
}
