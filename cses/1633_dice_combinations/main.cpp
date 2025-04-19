#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 1000005
#define DICE 6

using namespace std;

int memo[MAXN];

int solve(int n) {
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (memo[n]) {
        return memo[n] - 1;
    }
    int res = 0;
    for (int i = DICE; i > 0; i--) {
        res = (res + solve(n - i)) % MOD;
    }
    memo[n] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    cout << solve(n) << "\n";
}
