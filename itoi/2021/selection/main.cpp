#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1005

using namespace std;

int n, m;
int numbers[MAXN];
int memo[502000];

inline int hsh (int l, int r) {
    return (n - l) * (n - l + 1) / 2 + (r - l) - 2;
}

int find_sol (int l, int r) {
    // l and r are already at the right place
    // solve for the ones between l and r
    if (l + 1 >= r) {
        return memo[hsh(l, r)] = 0;
    }
    int cost = numbers[r] - numbers[l] - 1, s = INT_MAX >> 1;
    if (l + 2 == r && cost == 1) {
        cost = 0;
    }
    int mid = (l + r) >> 1;
    for (int i = max(l + 1, mid); i < r; i++) {
        // split at i
        int l_sol = memo[hsh(l, i)];
        int r_sol = memo[hsh(i, r)];
        if (l_sol >= s) break ;
        s = min(s, l_sol + r_sol);
    }
    for (int i = mid - 1; i > l; i--) {
        // split at i
        int l_sol = memo[hsh(l, i)];
        int r_sol = memo[hsh(i, r)];
        if (r_sol >= s) break ;
        s = min(s, l_sol + r_sol);
    }
    s += cost;
    return memo[hsh(l, r)] = s;
}

int main () {
    cin >> n >> m;
    fill(memo, memo + min((n + 2) * (n + 2), 502000), -1);
    numbers[0] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> numbers[i];
    }
    numbers[n + 1] = m;
    for (int sz = 0; sz <= n + 1; sz++) {
        for (int l = 0; l + sz <= n + 1; l++) {
            find_sol(l, l + sz);
        }
    }
    cout << memo[hsh(0, n + 1)] << "\n";
}
