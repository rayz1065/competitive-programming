#include <bits/stdc++.h>
#define MAXN 505
#define PRECISE_SOLUTION_W (505 * 505)

using namespace std;

typedef long long ll;

int n, m;
struct Job {
    int time;
    int value;

    bool operator < (const Job &b) const {
        // a.value / a.time > b.value / b.time
        // a.value * b.time > b.value * a.time
        return (ll) this->value * b.time > (ll) b.value * this->time;
    }
} jobs[MAXN];

ll memo[2][PRECISE_SOLUTION_W];

void fill_memo(int i) {
    for (int j = 0; j < PRECISE_SOLUTION_W; j++) {
        ll value = memo[(i + 1) % 2][j];
        if (j >= jobs[i].time) {
            // value if take i
            value = max(value, jobs[i].value + memo[i % 2][j - jobs[i].time]);
        }
        memo[i % 2][j] = value;
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].time;
    }
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].value;
    }

    sort(jobs, jobs + n);

    for (int i = 0; i < n; i++) {
        fill_memo(i);
    }

    // take jobs[0] until we are below PRECISE_SOLUTION_W
    int taken_count = max(0, m - PRECISE_SOLUTION_W) / jobs[0].time;
    if (m - taken_count * jobs[0].time >= PRECISE_SOLUTION_W) {
        taken_count += 1;
    }
    m -= taken_count * jobs[0].time;
    ll res = (ll) taken_count * jobs[0].value + memo[(n + 1) % 2][m];
    cout << res << "\n";
}
