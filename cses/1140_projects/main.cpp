#include <bits/stdc++.h>
#define MAXN 200005
#define MAXT 400005

using namespace std;

typedef long long ll;

int n, maxt;
int times[MAXT];
unordered_map<int, int> times_idx;
ll memo[MAXT];
vector<int> starting_at[MAXT];

struct {
    int a, b, p;
} projects[MAXN];

ll solve(int t) {
    if (t == maxt) {
        return 0;
    } else if (memo[t]) {
        return memo[t] - 1;
    }

    ll res = 0;
    res = solve(t + 1);
    for (auto i : starting_at[t]) {
        int end_t = times_idx[projects[i].b];
        res = max(res, solve(end_t) + projects[i].p);
    }

    memo[t] = res + 1;
    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, p;
        cin >> a >> b >> p;
        b++;
        projects[i] = {a, b, p};
        times[i * 2] = a;
        times[i * 2 + 1] = b;
    }

    sort(times, times + 2 * n);
    for (int i = 0; i < 2 * n;) {
        int t = times[i];
        for (; i < 2 * n && times[i] == t; i++);
        times_idx[t] = maxt++;
    }

    for (int i = 0; i < n; i++) {
        starting_at[times_idx[projects[i].a]].push_back(i);
    }

    cout << solve(0) << "\n";
}
