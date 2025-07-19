#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
pair<int, int> rnges[MAXN];
pair<int, int> events[MAXN * 2];
int contained_in[MAXN];
int contains[MAXN];

int fw_open[MAXN * 2], fw_closed[MAXN * 2];

void fw_add(int fw[], int i, int x) {
    for (i++; i < MAXN * 2; i += i & (-i)) {
        fw[i] += x;
    }
}

int fw_sum(int fw[], int i) {
    int res = 0;
    for (i++; i > 0; i -= i & (-i)) {
        res += fw[i];
    }
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> rnges[i].first >> rnges[i].second;
        events[i * 2] = {rnges[i].first, i + 1};
        events[i * 2 + 1] = {rnges[i].second, -i - 1};
    }
    sort(events, events + 2 * n);
    for (int i = 0, n_times = 0; i < 2 * n; n_times++) {
        int t = events[i].first;
        for (; events[i].first == t; i++) {
            int range_id = abs(events[i].second) - 1;
            bool added = events[i].second > 0;
            events[i].first = n_times;
            if (added) {
                rnges[range_id].first = n_times;
            } else {
                rnges[range_id].second = n_times;
            }
        }
    }

    for (int i = 0; i < 2 * n;) {
        int t = events[i].first;

        vector<int> ff;
        for (; i < 2 * n && events[i].first == t; i++) {
            int range_id = abs(events[i].second) - 1;
            bool added = events[i].second > 0;
            if (added) {
                fw_add(fw_open, t, 1);
            } else {
                ff.push_back(range_id);
                contained_in[range_id] =
                    fw_sum(fw_open, rnges[range_id].first) - 1;
                fw_add(fw_closed, rnges[range_id].first, 1);
            }
        }

        for (auto range_id : ff) {
            fw_add(fw_open, rnges[range_id].first, -1);
            contains[range_id] = fw_sum(fw_closed, t) -
                                 fw_sum(fw_closed, rnges[range_id].first - 1) -
                                 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << contains[i] << " \n"[i + 1 == n];
    }
    for (int i = 0; i < n; i++) {
        cout << contained_in[i] << " \n"[i + 1 == n];
    }
}
