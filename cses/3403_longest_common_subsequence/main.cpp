#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n, m;
int memo[MAXN][MAXN];
int values[2][MAXN];

int _solve(int i1, int i2) {
    if (i1 == n || i2 == m) {
        return 0;
    } else if (memo[i1][i2]) {
        return memo[i1][i2] - 1;
    }

    int res = 0;
    res = max(_solve(i1 + 1, i2), _solve(i1, i2 + 1));
    if (values[0][i1] == values[1][i2]) {
        res = max(res, _solve(i1 + 1, i2 + 1) + 1);
    }
    memo[i1][i2] = res + 1;
    return res;
}

int solve(int i1, int i2, vector<int> &solution) {
    if (i1 == n || i2 == m) {
        return 0;
    }

    int res = _solve(i1, i2);
    if (res == _solve(i1 + 1, i2)) {
        solve(i1 + 1, i2, solution);
    } else if (res == _solve(i1, i2 + 1)) {
        solve(i1, i2 + 1, solution);
    } else {
        solution.push_back(values[0][i1]);
        solve(i1 + 1, i2 + 1, solution);
    }
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int j = 0; j < 2; j++) {
        int limit = j == 0 ? n : m;
        for (int i = 0; i < limit; i++) {
            cin >> values[j][i];
        }
    }

    vector<int> solution;
    cout << solve(0, 0, solution) << "\n";
    for (auto i : solution) {
        cout << i << " ";
    }
    cout << "\n";
}
