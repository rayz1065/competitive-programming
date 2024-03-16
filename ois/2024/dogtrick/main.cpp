#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, k_tricks;
int competition[MAXN];
unordered_set<ll> performable_tricks;
int memo[MAXN];

ll to_trick_key(int a, int b) {
    return (ll) a * MAXN + b;
}

bool is_performable(int a, int b) {
    auto key = to_trick_key(a, b);
    return performable_tricks.find(key) != performable_tricks.end();
}

int solve(int i) {
    if (i == n) {
        return 0;
    } else if (memo[i] != 0) {
        return memo[i] - 1;
    } else if (competition[i] == k_tricks + 1) {
        return INT_MIN >> 1;
    }

    int res = INT_MIN >> 1;
    for (int j = i + 1; j <= i + 2 && j <= n; j++) {
        if (is_performable(competition[i], competition[j])) {
            res = max(res, solve(j) + 1);
        }
    }

    memo[i] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k_tricks;
    for (int i = 0; i < n; i++) {
        cin >> competition[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        auto key = to_trick_key(a, b);
        performable_tricks.insert(key);
    }

    // performance[n] = 0;
    for (int a = 1; a <= k_tricks; a++) {
        auto key = to_trick_key(a, 0); // dummy trick
        performable_tricks.insert(key);
    }

    int res = max(solve(0), solve(1));
    res = max(res, 0);
    cout << res << "\n";
}
