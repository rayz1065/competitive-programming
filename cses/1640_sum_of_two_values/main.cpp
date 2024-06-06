#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n, target_sum;
pair<int, int> values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> target_sum;
    for (int i = 0; i < n; i++) {
        cin >> values[i].first;
        values[i].second = i;
    }

    sort(values, values + n);

    for (int i = 0, j = n - 1; i < n; i++) {
        for (; j > i && values[i].first + values[j].first > target_sum; j--);

        if (j > i && values[i].first + values[j].first == target_sum) {
            cout << values[i].second + 1 << " " << values[j].second + 1 << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
}
