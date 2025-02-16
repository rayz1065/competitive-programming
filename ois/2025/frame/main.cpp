#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    ll a;
    cin >> n >> m >> a;

    int res = 0;
    for (int i = 1; (ll)i * i <= a; i++) {
        if (a % i) {
            continue;
        }
        if (i >= n && (a / i) >= m) {
            res += 1;
        }
        if (i * i < a && i >= m && (a / i) >= n) {
            res += 1;
        }
    }

    cout << res << "\n";
}
