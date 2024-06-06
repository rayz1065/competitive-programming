#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int coins[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    sort(coins, coins + n);

    ll res = 0;
    for (int i = 0; i < n && coins[i] <= res + 1; i++) {
        res += coins[i];
    }

    cout << res + 1 << "\n";
}
