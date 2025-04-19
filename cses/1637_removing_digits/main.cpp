#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int memo[MAXN];

vector<int> get_digits(int n) {
    vector<int> res;
    for (; n > 0; n /= 10) {
        res.push_back(n % 10);
    }
    return res;
}

int solve(int n) {
    if (n == 0) {
        return 0;
    } else if (memo[n]) {
        return memo[n] - 1;
    }

    int res = INT_MAX >> 1;

    auto digits = get_digits(n);
    for (auto j : digits) {
        if (j && n - j >= 0) {
            res = min(res, solve(n - j) + 1);
        }
    }

    memo[n] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    cout << solve(n) << "\n";
}
