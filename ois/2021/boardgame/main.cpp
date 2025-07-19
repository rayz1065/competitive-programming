#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, l, u;
    cin >> n >> l >> u;

    int lb = n / u + (n % u > 0);
    int ub = n / l;

    cout << (lb <= ub ? lb : -1) << "\n";
}
