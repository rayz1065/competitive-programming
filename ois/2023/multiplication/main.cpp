#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void add_found (ll n, vector<bool> &found) {
    for (; n; n /= 10) found[n % 10] = true;
}

bool all_found (vector<bool> &found) {
    for (auto j: found) {
        if (!j) {
            return false;
        }
    }
    return true;
}

int tc () {
    int n;
    cin >> n;
    int mul = 1;
    vector<bool> found(10, 0);
    for (mul = 1; !all_found(found); mul++) {
        add_found((ll) n * mul, found);
    }
    return mul - 1;
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) cout << tc() << "\n";
}
