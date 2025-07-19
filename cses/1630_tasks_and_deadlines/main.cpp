#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
pair<int, int> tasks[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].first >> tasks[i].second;
    }
    sort(tasks, tasks + n);

    ll res = 0, curr_t = 0;
    for (int i = 0; i < n; i++) {
        curr_t += tasks[i].first;
        res += tasks[i].second - curr_t;
    }

    cout << res << "\n";
}
