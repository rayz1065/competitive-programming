#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
struct {
    int from;
    int to;
    int credits;
} courses[MAXN];
int all_times[MAXN * 2];
unordered_map<int, int> time_index;
vector<int> courses_starting_at[2 * MAXN];
int memo[2 * MAXN];

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int from, to, credits;
        cin >> from >> to >> credits;
        courses[i] = {from, to, credits};
        all_times[i * 2] = from;
        all_times[i * 2 + 1] = to;
    }

    sort(all_times, all_times + 2 * n);
    int curr_index = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i > 0 && all_times[i] != all_times[i - 1]) {
            curr_index += 1;
        }
        time_index[all_times[i]] = curr_index;
    }

    for (int i = 0; i < n; i++) {
        courses[i].from = time_index[courses[i].from];
        courses[i].to = time_index[courses[i].to];
        courses_starting_at[courses[i].from].push_back(i);
    }

    for (int t = 2 * n - 1; t >= 0; t--) {
        int res = memo[t + 1];

        for (auto i : courses_starting_at[t]) {
            res = max(res, memo[courses[i].to + 1] + courses[i].credits);
        }

        memo[t] = res;
    }

    cout << memo[0] << "\n";
}
