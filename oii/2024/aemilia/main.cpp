#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

vector<int> added_at[MAXN];

vector<int> verifica(int n, vector<int> times) {
    vector<int> res;

    for (int i = 0; i < n; i++) {
        added_at[times[i]].push_back(i);
    }

    int loc_min = INT_MAX >> 1, loc_max = INT_MIN >> 1;
    int cur_min = INT_MAX >> 1, cur_max = INT_MIN >> 1;

    for (int i = 0; i < n; i++) {
        for (auto j : added_at[i]) {
            loc_min = min(loc_min, j);
            loc_max = max(loc_max, j);
        }

        if (loc_min > loc_max) {
            continue;
        }

        int length = loc_max - loc_min;
        if (length > i) {
            return {};
        }

        if (cur_min == INT_MAX >> 1) {
            cur_min = loc_min;
            cur_max = loc_min;
            res.push_back(loc_min);
        }

        while (cur_min > loc_min) {
            cur_min -= 1;
            res.push_back(cur_min);
        }
        while (cur_max < loc_max) {
            cur_max += 1;
            res.push_back(cur_max);
        }
    }

    return res;
}
