#include <bits/stdc++.h>
#define MAXN 1000005
#define MOD(x) ((x) % 1000000007)

using namespace std;

typedef long long ll;

int memo[MAXN][2];

int solve_w(int n, bool flag) {
    if (n == 0) {
        return 1;
    } else if (memo[n][flag]) {
        return memo[n][flag] - 1;
    }

    int res = 0;
    if (flag) {
        res = MOD(res + (ll)4 * solve_w(n - 1, 1));
        res = MOD(res + solve_w(n - 1, 0));
    } else {
        res = MOD(res + (ll)2 * solve_w(n - 1, 0));
        res = MOD(res + solve_w(n - 1, 1));
    }

    memo[n][flag] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int res = MOD(solve_w(n - 1, 0) + solve_w(n - 1, 1));
        cout << res << "\n";
    }
}
