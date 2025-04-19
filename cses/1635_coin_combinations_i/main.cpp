#include <bits/stdc++.h>
#define MAXN 105
#define MAXV 1000005
#define MOD 1000000007

using namespace std;

int coins[MAXN];
int memo[MAXV];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, desired_sum;
    cin >> n >> desired_sum;

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    sort(coins, coins + n);

    memo[0] = 1;
    for (int j = 1; j <= desired_sum; j++) {
        for (int i = 0; i < n && j - coins[i] >= 0; i++) {
            memo[j] = (memo[j] + memo[j - coins[i]]) % MOD;
        }
    }

    cout << memo[desired_sum] << "\n";
}
