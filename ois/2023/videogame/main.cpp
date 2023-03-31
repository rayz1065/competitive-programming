#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

pair<int, int> intervals_a[MAXN], intervals_b[MAXN];

int main () {
    int t_bored;
    int n, m;
    cin >> t_bored;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> intervals_a[i].first >> intervals_a[i].second;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> intervals_b[i].first >> intervals_b[i].second;
    }

    int i = 0, j = 0, time_together = 0;
    while (i < n) {
        // find corresponding b interval
        while (j < m && intervals_b[j].second < intervals_a[i].first) {
            j++;
        }
        // got bored before?
        int leave_time = min(intervals_a[i].first + t_bored, intervals_a[i].second);
        if (j == m || intervals_b[j].first > leave_time) {
            i++;
            continue ;
        }
        // play together
        if (intervals_b[j].second < intervals_a[i].second) {
            time_together += intervals_b[j].second - max(intervals_a[i].first, intervals_b[j].first) + 1;
            intervals_a[i].first = intervals_b[j].second + 1;
            j++;
        } else {
            time_together += intervals_a[i].second - max(intervals_a[i].first, intervals_b[j].first) + 1;
            i++;
        }
    }
    cout << time_together << "\n";
}
