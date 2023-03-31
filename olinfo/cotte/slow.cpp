#include <bits/stdc++.h>
#define MAXN 5000005

using namespace std;

int m_count, f_count, n_couples;
pair<int, int> couples[MAXN];
int memo[10005][10005];

int solve (int m, int f) {
    if (m >= m_count || f >= f_count) {
        return 0;
    }
    if (memo[m][f] != -1) {
        return memo[m][f];
    }
    int s = max(solve(m + 1, f), solve(m, f + 1));
    for (int i = 0; i < n_couples; i++) {
        auto couple = couples[i];
        if (couple.first >= m && couple.second >= f) {
            s = max(s, solve(couple.first + 1, couple.second + 1) + 2);
        }
    }
    // printf("memo[%d][%d] = %d\n", m, f, s);
    return memo[m][f] = s;
}

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> m_count >> f_count >> n_couples;
    for (int i = 0; i < m_count; i++) {
        for (int j = 0; j < f_count; j++) {
            memo[i][j] = -1;
        }
    }
    for (int i = 0; i < n_couples; i++) {
        cin >> couples[i].first >> couples[i].second;
        couples[i].first--;
        couples[i].second--;
    }

    cout << solve(0, 0) << "\n";

    // for (int i = 0; i < m_count; i++) {
    //     for (int j = 0; j < f_count; j++) {
    //         cout << solve(i, j) << " \n"[j == f_count - 1];
    //     }
    // }
}