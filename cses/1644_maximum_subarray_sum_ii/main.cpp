#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, values[MAXN];
ll prefix_sums[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
        prefix_sums[i + 1] = prefix_sums[i] + values[i];
    }

    multiset<ll> curr;
    ll res = LLONG_MIN >> 1, sum = 0;
    for (int i = 0; i < n; i++) {
        if (i >= b) {
            curr.erase(curr.find(prefix_sums[i - b]));
        }
        if (i + 1 >= a) {
            curr.insert(prefix_sums[i - a + 1]);
        }

        if (curr.size() > 0) {
            res = max(res, prefix_sums[i + 1] - *curr.begin());
        }
    }

    cout << res << "\n";
}
