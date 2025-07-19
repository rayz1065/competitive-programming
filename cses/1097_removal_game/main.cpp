#include <bits/stdc++.h>
#define MAXN 5005
#define NINF (INT_MIN >> 1)

using namespace std;

typedef long long ll;

int n;
int values[MAXN];
pair<ll, ll> memo[MAXN][MAXN];
bool solved[MAXN][MAXN];

pair<ll, ll> solve(int i, int j) {
    if (i > j) {
        return {0, 0};
    } else if (solved[i][j]) {
        return memo[i][j];
    }

    auto child_1 = solve(i + 1, j);
    child_1.second += values[i];
    auto child_2 = solve(i, j - 1);
    child_2.second += values[j];

    if (child_1.second < child_2.second) {
        swap(child_1, child_2);
    }
    swap(child_1.first, child_1.second);

    memo[i][j] = child_1;
    solved[i][j] = true;

    return child_1;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    auto res = solve(0, n - 1);
    cout << res.first << "\n";
}
