#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

typedef long long ll;

int n;
pair<int, int> values[MAXN];

inline int idxconv(int i) { return values[i].second; }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int target;
    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> values[i].first;
        values[i].second = i + 1;
    }

    // split into two subarrays
    int n1 = n / 2;

    vector<pair<int, pair<int, int>>> sums[2];
    for (int i = 0; i < n; i++) {
        int limit = i < n1 ? n1 : n;
        for (int j = i + 1; j < limit; j++) {
            if (values[i].first + values[j].first < target) {
                sums[i >= n1].push_back(
                    {values[i].first + values[j].first, {i + 1, j + 1}});
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        sort(sums[i].begin(), sums[i].end());
    }

    for (int i = 0, j = sums[1].size() - 1; i < sums[0].size() && j >= 0; i++) {
        for (; j >= 0 && sums[0][i].first + sums[1][j].first > target; j--);
        if (j >= 0 && sums[0][i].first + sums[1][j].first == target) {
            cout << sums[0][i].second.first << " " << sums[0][i].second.second
                 << " " << sums[1][j].second.first << " "
                 << sums[1][j].second.second << "\n";
            return 0;
        }
    }
    sort(values, values + n);

    for (int k = 0; k < 2; k++) {
        int start = k == 0 ? 0 : n1;
        int limit = k == 0 ? n1 : n;
        for (int i1 = start; i1 < limit; i1++) {
            for (int i2 = i1 + 1; i2 < limit; i2++) {
                for (int i3 = i2 + 1, i4 = n - 1; i3 < limit && i4 >= 0; i3++) {
                    for (; i4 >= 0 &&
                           ((ll)values[i1].first + values[i2].first +
                                    values[i3].first + values[i4].first >
                                target ||
                            i1 == i4 || i2 == i4 || i3 == i4);
                         i4--);
                    if (i4 >= 0 && (ll)values[i1].first + values[i2].first +
                                           values[i3].first +
                                           values[i4].first ==
                                       target) {
                        cout << idxconv(i1) << " " << idxconv(i2) << " "
                             << idxconv(i3) << " " << idxconv(i4) << "\n";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}
