#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int target;
    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    unordered_map<ll, int> prefix_sums;
    prefix_sums.reserve(n + 5);
    prefix_sums[0] = 1;

    ll res = 0, prefix_sum = 0;
    for (int i = 0; i < n; i++) {
        prefix_sum += values[i];
        auto found = prefix_sums.find((prefix_sum - target));
        if (found != prefix_sums.end()) {
            res += found->second;
        }
        prefix_sums[prefix_sum] += 1;
    }

    cout << res << "\n";
}
