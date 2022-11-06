#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 5005
#define MAXX 10005

using namespace std;

int n;
int memo[2][MAXX];
int prob[MAXN], cost[MAXN];

void calc_sol (int i, int rem_coins) {
    int s = memo[(i + 1) % 2][rem_coins]; // skip curr
    if (rem_coins >= cost[i]) {
        s = max(s, memo[(i + 1) % 2][rem_coins - cost[i]] + prob[i]);
    }
    memo[i % 2][rem_coins] = s;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> prob[i] >> cost[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int rem_coins = 0; rem_coins <= x; rem_coins++) {
            calc_sol(i, rem_coins);
        }
    }
    cout << memo[n % 2][x] << "\n";
}
