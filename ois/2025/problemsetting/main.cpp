#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int a[MAXN], b[MAXN];

bool solution_exists(int target) {
    int leftover = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] + leftover >= target) {
            leftover = b[i];
        } else if (a[i] + b[i] >= target - leftover) {
            leftover = a[i] - target + b[i] + leftover;
        } else {
            return false;
        }
    }

    return true;
}

int solve() {
    int l = 1, r = INT_MAX;
    int res = 0;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (solution_exists(m)) {
            res = m, l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n - 1; i++) {
            cin >> b[i];
        }

        b[n - 1] = 0;

        cout << solve() << "\n";
    }
}
