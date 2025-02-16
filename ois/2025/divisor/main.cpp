#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve(ll a, ll b, ll k) {
    vector<ll> divisors;

    ll sum = a + b + k;
    for (ll i = 2; i * i <= sum; i++) {
        if (sum % i == 0) {
            divisors.push_back(i);
            divisors.push_back(sum / i);
        }
    }

    ll res = 1;

    for (auto i : divisors) {
        ll effective_a = a + (i - a % i) % i;
        ll effective_b = b + (i - b % i) % i;
        if (effective_a - a + effective_b - b <= k) {
            res = max(res, i);
        }
    }

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int a, b, k;
        cin >> a >> b >> k;

        cout << solve(a, b, k) << "\n";
    }
}
