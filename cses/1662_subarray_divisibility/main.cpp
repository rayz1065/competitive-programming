#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, values[MAXN], freqs[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    ll res = 0, prefix_sum = 0;
    freqs[0] += 1;
    for (int i = 0; i < n; i++) {
        prefix_sum += values[i];
        int bucket_idx = (prefix_sum % n + n) % n;
        res += freqs[bucket_idx];
        freqs[bucket_idx] += 1;
    }

    cout << res << "\n";
}
