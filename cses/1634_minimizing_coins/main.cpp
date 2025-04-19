#include <bits/stdc++.h>
#define MAXN 105
#define MAXV 1000005

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

    memo[0] = 0;
    for (int i = 1; i <= desired_sum; i++) {
        int res = INT_MAX >> 1;
        for (int j = 0; j < n && i - coins[j] >= 0; j++) {
            res = min(res, memo[i - coins[j]] + 1);
        }
        memo[i] = res;
    }

    int res = memo[desired_sum];
    cout << (res >= (INT_MAX >> 1) ? -1 : res) << "\n";
}
