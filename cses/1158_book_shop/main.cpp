#include <bits/stdc++.h>
#define MAXV 100005
#define MAXN 1005

using namespace std;

int values[MAXN];
int weights[MAXN];
int memo[MAXN][MAXV];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, capacity;
    cin >> n >> capacity;

    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = capacity; j >= 0; j--) {
            int res = memo[i + 1][j];
            if (j + weights[i] <= capacity) {
                res = max(res, memo[i + 1][j + weights[i]] + values[i]);
            }
            memo[i][j] = res;
        }
    }

    cout << memo[0][0] << "\n";
}
