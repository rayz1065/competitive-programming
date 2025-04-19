#include <bits/stdc++.h>
#define MAXN 45

using namespace std;

typedef long long ll;

int n, half_n, desired_sum;
int values[MAXN];
unordered_map<int, ll> freq;

void compute_freq(int i, int j) {
    if (j > desired_sum) {
        return;
    } else if (i == half_n) {
        freq[j] += 1;
        return;
    }

    compute_freq(i + 1, j + values[i]);
    compute_freq(i + 1, j);
}

ll solve(int i, int j) {
    if (j > desired_sum) {
        return 0;
    } else if (i == n) {
        return freq[desired_sum - j];
    }

    return solve(i + 1, j + values[i]) + solve(i + 1, j);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> desired_sum;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    sort(values, values + n);

    half_n = max(0, n / 2);
    compute_freq(0, 0);

    cout << solve(half_n, 0) << "\n";
}
