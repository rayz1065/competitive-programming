#include <bits/stdc++.h>
#define MAXN 105
#define MAXV 1000005
#define MOD 1000000007

using namespace std;

int n;
int coins[MAXN];
int memo[MAXN][MAXV];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int desired_sum;
    cin >> n >> desired_sum;

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    sort(coins, coins + n);

    for (int i = n - 1; i >= 0; i--) {
        memo[i][0] = 1;
        for (int j = coins[i]; j <= desired_sum; j++) {
            memo[i][j] = (memo[i + 1][j] + memo[i][j - coins[i]]) % MOD;
        }
    }

    cout << memo[0][desired_sum] << "\n";
}
