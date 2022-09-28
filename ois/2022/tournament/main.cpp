#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

int fastin(int &v) {
    v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n_people;
    fastin(n_people);

    int best = 0;
    int greatest_sub = 0, lowest_sum = INT_MAX >> 1;
    for (int i = 0; i < n_people; i++) {
        // max(j - i + s[i] - s[j], j - i + s[j] - s[i])
        // max((s[i] - i) - (s[j] - j), - (s[i] + i) + (s[j] + j))
        // max(best_sub - sub, sum - best_sum)
        int style;
        fastin(style);
        int sub = style - i, sum = style + i;
        best = max(best, greatest_sub - sub);
        best = max(best, sum - lowest_sum);

        greatest_sub = max(greatest_sub, sub);
        lowest_sum = min(lowest_sum, sum);

        // cout << "> " << i << " " << style << " sum = " << sum << ", sub = " << sub << "\n";
        // cout << "best = " << best << "\n";

    }
    cout << best << "\n";
    return 0;
}
