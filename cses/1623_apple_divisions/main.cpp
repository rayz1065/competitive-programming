#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, values[25];
ll sum;

ll solve(int i, ll curr) {
    if (i >= n) {
        ll other = sum - curr;
        return llabs(curr - other);
    }

    return min(solve(i + 1, curr), solve(i + 1, curr + values[i]));
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
        sum += values[i];
    }

    cout << solve(0, 0) << "\n";
}
