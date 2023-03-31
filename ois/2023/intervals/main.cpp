#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int flag[MAXN * 2];
pair<int, int> shows[MAXN];
int sorted_shows[MAXN];
pair<int, pair<bool, int>> all_times[MAXN * 2];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n = fastin();
    int s = 0;
    for (int i = 0; i < n; i++) {
        int a = fastin(), b = fastin();
        shows[i] = { a, b };
        all_times[2 * i] = { a, { false, i } };
        all_times[2 * i + 1] = { b, { true, i } };
    }
    sort(all_times, all_times + 2 * n);
    int k_new_idx = 0;
    int sorted_shows_id = 0;
    for (int i = 0; i < 2 * n; i++) {
        int show_id = all_times[i].second.second;
        bool is_end_time = all_times[i].second.first;
        if (i > 0 && all_times[i].first > all_times[i - 1].first) k_new_idx++;
        if (is_end_time) shows[show_id].second = k_new_idx;
        else {
            shows[show_id].first = k_new_idx;
            sorted_shows[sorted_shows_id++] = show_id;
        }
    }
    for (int i = 0; i < n; i++) {
        int show_id = sorted_shows[i];
        int a = shows[show_id].first, b = shows[show_id].second;
        if (flag[a]) {
            flag[a] -= 1;
        } else {
            s++;
        }
        flag[b] += 1;
    }
    cout << s << "\n";
}
