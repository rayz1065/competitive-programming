#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

bool is_prime[MAXN];

void eratostene() {
    fill(is_prime + 2, is_prime + MAXN, true);
    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            for (ll j = (ll)i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    eratostene();

    int res = 0;
    for (int i = 2; i <= n; i++) {
        res += is_prime[i];
    }

    cout << res << "\n";
}
