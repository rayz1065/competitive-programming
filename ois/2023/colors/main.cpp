#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 1000005

using namespace std;

typedef long long ll;

int available_endings[MAXN];
int same_color[MAXN];

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> same_color[i];
    }

    int total_endings = 0;
    ll s = 1;
    for (int i = 0; i < n; i++) {
        int ways = 1;
        int freq_ahead = same_color[i];
        if (freq_ahead > 0) {
            ways = available_endings[freq_ahead - 1];
            available_endings[freq_ahead - 1] -= 1;
        } else {
            total_endings += 1;
        }
        available_endings[freq_ahead] += 1;
        s = (s * ways) % MOD;
    }

    // choose factorial_endings colors, rearrange
    for (int i = k - total_endings + 1; i <= k; i++) {
        s = (s * i) % MOD;
    }

    cout << s << "\n";
}
