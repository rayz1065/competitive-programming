#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 100005

using namespace std;

int n;
int lights[MAXN];
int memo[MAXN];

int solve (int i) {
    if (i >= n) {
        return 0;
    }
    if (memo[i] == INT_MAX >> 1) {
        int by_skipping = solve(i + 2) + lights[i + 1];
        int by_waiting = solve(i + 1) + lights[i];
        memo[i] = min(by_skipping, by_waiting);
    }
    return memo[i];
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> lights[i];
    }
    fill(memo, memo + n, INT_MAX >> 1);

    cout << solve(0) << "\n";
}