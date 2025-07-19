#include <bits/stdc++.h>
#define MAXN 20
#define POWMAXN ((1 << MAXN) + 5)

using namespace std;

int n, x;
int weights[MAXN];
pair<int, int> memo[POWMAXN];

pair<int, int> solve(int flag) {
    if (flag == 0) {
        return {0, 0};
    } else if (memo[flag].first) {
        auto res = memo[flag];
        return {res.first - 1, res.second};
    }

    pair<int, int> res = {INT_MAX >> 1, 0};

    for (int i = 0; i < n; i++) {
        int flag_bit = 1 << i;
        if (flag & flag_bit) {
            auto prev = solve(flag & (~flag_bit));
            int rides = prev.first, remaining_weight = prev.second;
            if (remaining_weight + weights[i] > x) {
                remaining_weight = 0;
                rides += 1;
            }
            remaining_weight += weights[i];
            if (rides < res.first ||
                (rides == res.first && remaining_weight < res.second)) {
                res = {rides, remaining_weight};
            }
        }
    }

    memo[flag] = {res.first + 1, res.second};
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    sort(weights, weights + n);

    auto res = solve((1 << n) - 1);
    int rides = res.first + (res.second > 0);

    cout << rides << "\n";
}
