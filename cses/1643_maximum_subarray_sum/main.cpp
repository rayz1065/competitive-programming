#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int values[MAXN];
ll prefix_sums[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    for (int i = 0; i < n; i++) {
        prefix_sums[i + 1] = prefix_sums[i] + values[i];
    }

    ll curr_min = 0, best = LLONG_MIN >> 1;
    for (int i = 0; i < n; i++) {
        curr_min = min(curr_min, prefix_sums[i]);
        best = max(best, prefix_sums[i + 1] - curr_min);
    }

    cout << best << "\n";
}
