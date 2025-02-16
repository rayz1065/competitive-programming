#include <bits/stdc++.h>
#define MAXN 100005
#define MAXL 1000005

using namespace std;

int n;
pair<int, int> cows[MAXN];

int left_ft[MAXL + 5], right_ft[MAXL + 5];

void ft_add(int ft[], int index, int amount) {
    for (index += 1; index < MAXL; index += index & (-index)) {
        ft[index] += amount;
    }
}

int ft_sum(int ft[], int index) {
    int res = 0;
    for (index += 1; index > 0; index -= index & (-index)) {
        res += ft[index];
    }
    return res;
}

/**
 * find top-bottom split
 */
int evenly_split() {
    int best = INT_MAX >> 1;
    int l = 0, r = MAXL - 1;

    int total_left = ft_sum(left_ft, MAXL - 1);
    int total_right = ft_sum(right_ft, MAXL - 1);

    while (l <= r) {
        int m = (l + r) >> 1;
        int top_left = ft_sum(left_ft, m);
        int top_right = ft_sum(right_ft, m);
        int bottom_left = total_left - top_left;
        int bottom_right = total_right - top_right;

        int worst = max({top_left, top_right, bottom_left, bottom_right});
        if (worst < best) {
            best = worst;
        }

        if (worst == top_left || worst == top_right) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return best;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("balancing.in", ios::in);
    cout.open("balancing.out", ios::out);
#endif
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
        ft_add(right_ft, cows[i].second, 1);
    }
    sort(cows, cows + n);

    int cow_idx = 0, best = INT_MAX >> 1;
    while (cow_idx < n) {
        int target_x = cows[cow_idx].first + 1;  // split on x
        while (cow_idx < n && cows[cow_idx].first <= target_x) {
            ft_add(left_ft, cows[cow_idx].second, 1);
            ft_add(right_ft, cows[cow_idx].second, -1);
            cow_idx += 1;
        }

        best = min(best, evenly_split());
    }

    cout << best << "\n";
}
