#include <bits/stdc++.h>
#define MAXN 10005
#define MAXC 1000005

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> horizontal[MAXC * 2];
// y -> { x, delta }
vector<pair<int, pair<int, int>>> vertical;

int fenwick[MAXC * 2];

void fw_add(int idx, int value) {
    for (idx += 1; idx < MAXC * 2; idx += idx & (-idx)) {
        fenwick[idx] += value;
    }
}

int fw_sum(int idx) {
    int res = 0;
    for (idx += 1; idx > 0; idx -= idx & (-idx)) {
        res += fenwick[idx];
    }
    return res;
}

int fw_range_sum(int a, int b) {
    if (a == 0) {
        return fw_sum(b);
    }
    return fw_sum(b) - fw_sum(a - 1);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2) {
            vertical.push_back({y1, {x1, +1}});
            vertical.push_back({y2, {x2, -1}});
        } else {
            horizontal[y1 + MAXC].push_back({x1, x2});
        }
    }

    sort(vertical.begin(), vertical.end());
    int vertical_idx = 0;

    ll res = 0;

    for (int y = -MAXC; y < MAXC; y++) {
        while (vertical_idx < (int)vertical.size() &&
               vertical[vertical_idx].first == y) {
            int x = vertical[vertical_idx].second.first;
            int value = vertical[vertical_idx].second.second;
            fw_add(x + MAXC, value);
            vertical_idx += 1;
        }

        for (auto line : horizontal[y + MAXC]) {
            res += fw_range_sum(line.first + MAXC, line.second + MAXC);
        }
    }

    cout << res << "\n";
}
