#include <bits/stdc++.h>
#define MAXN 5005

using namespace std;

int n;
pair<int, int> values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int target;
    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> values[i].first;
        values[i].second = i;
    }
    sort(values, values + n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1, k = n - 1; j < n && k >= 0; j++) {
            int missing = target - values[i].first - values[j].first;
            for (; k >= 0 && (values[k].first > missing || i == k || j == k);
                 k--);
            if (k >= 0 && values[k].first == missing) {
                cout << values[i].second + 1 << " " << values[j].second + 1
                     << " " << values[k].second + 1;
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}
