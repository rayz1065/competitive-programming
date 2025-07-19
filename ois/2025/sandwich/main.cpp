#include <bits/stdc++.h>
#define MAXN 400005

using namespace std;

typedef long long ll;

int n;
int values[MAXN];
ll prefix_sums[MAXN];
int memo[MAXN];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    bool minus = c == '-';
    if (minus) {
        c = getchar_unlocked();
    }
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v - minus * 2 * v;
}

int main() {
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();
    for (int i = 0; i < n; i++) {
        values[i] = fastin();
        prefix_sums[i + 1] = prefix_sums[i] + values[i];
    }

    set<pair<ll, int>> thresholds;
    thresholds.insert({prefix_sums[n], 0});

    for (int i = n - 1; i >= 0; i--) {
        auto found = thresholds.upper_bound({prefix_sums[i] + 1, -1});
        if (found == thresholds.end()) {
            continue;
        }

        memo[i] = found->second + 1;

        if (found != thresholds.begin()) {
            found--;
            if (found->first < prefix_sums[i]) {
                thresholds.erase(found);
                thresholds.insert({prefix_sums[i], memo[i]});
            }
        } else {
            thresholds.insert({prefix_sums[i], memo[i]});
        }
    }

    cout << memo[0] << "\n";
}
