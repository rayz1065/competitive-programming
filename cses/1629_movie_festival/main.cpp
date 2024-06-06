#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
pair<int, int> movies[MAXN];
int memo[MAXN];

int find_next(int start_time) {
    int l = 0, r = n - 1, s = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (movies[mid].first < start_time) {
            l = mid + 1;
        } else {
            s = mid;
            r = mid - 1;
        }
    }

    return s;
}

int solve(int i) {
    if (i == n) {
        return 0;
    } else if (memo[i] != 0) {
        return memo[i] - 1;
    }

    int j = find_next(movies[i].second);
    memo[i] = max(solve(i + 1), solve(j) + 1) + 1;
    return memo[i] - 1;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
    }

    sort(movies, movies + n);

    cout << solve(0) << "\n";
}
