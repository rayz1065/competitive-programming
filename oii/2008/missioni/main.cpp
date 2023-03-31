#include <bits/stdc++.h>
#define MAXN 105
#define MAXD 370

using namespace std;

int n;
pair<int, int> missions[MAXN];
bool completed[MAXN];
int memo[MAXN][MAXD];

int solve (int i, int t) {
    if (i == n) return 0;
    if (memo[i][t] != -1) return memo[i][t];
    memo[i][t] = solve(i + 1, t);
    if (t + missions[i].first - 1 <= missions[i].second) {
        memo[i][t] = max(memo[i][t], solve(i + 1, t + missions[i].first) + 1);
    }
    return memo[i][t];
}

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> n;
    for (int i = 0; i < n; i++) fill(memo[i], memo[i] + MAXD, -1);
    for (int i = 0; i < n; i++) {
        cin >> missions[i].first >> missions[i].second;
    }
    cout << solve(0, 1) << "\n";
}
