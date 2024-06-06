#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
pair<int, int> values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i].first;
        values[i].second = i;
    }

    sort(values, values + n);

    int res = 1;

    for (int i = 0, j = -1; i < n; i++) {
        if (values[i].second < j) {
            res += 1;
        }

        j = values[i].second;
    }

    cout << res << "\n";
}
