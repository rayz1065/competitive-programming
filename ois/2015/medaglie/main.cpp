#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int memo[MAXN][2];
int medals[MAXN];
int values[] = {100, 300, 500};

int solve(int i, bool turn) {
    if (memo[i][turn] != 0) {
        return memo[i][turn] - 1;
    } else if (i == n) {
        return 0;
    }
    int curr_value = 0;
    int res = turn ? 0 : INT_MAX >> 1;
    for (int j = 0; j < 3 && i + j < n; j++) {
        curr_value += values[medals[i + j]];
        int sub = solve(i + j + 1, !turn);
        res = turn ? max(res, curr_value + sub) : min(res, sub);
    }

    memo[i][turn] = res + 1;
    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> medals[i];
    }
    reverse(medals, medals + n);

    cout << solve(0, true) << "\n";
}
