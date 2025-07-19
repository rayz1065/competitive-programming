#include <bits/stdc++.h>
#define MAXN 200005
#define INF (INT_MAX >> 1)

using namespace std;

int n;
int values[MAXN];
int res[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    fill(res + 1, res + n, INF);
    int solution = 0;
    for (int i = 0; i < n; i++) {
        auto lb = lower_bound(res, res + n, values[i]);
        int j = lb - res;
        res[j] = values[i];
        solution = max(solution, j);
    }

    cout << solution << "\n";
}
