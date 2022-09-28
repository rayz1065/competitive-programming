#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;

int n_lights, l_street_len;
int r_skippable, t_half_period, xs[MAXN], memo[2][MAXN];

void read_input() {
    cin >> n_lights >> r_skippable >> t_half_period >> l_street_len;
    for (int i = 0; i < n_lights; i++) {
        cin >> xs[i];
    }
    xs[n_lights++] = l_street_len;
}

int dist_to_next (int semaphore_idx) {
    if (semaphore_idx == n_lights - 1) {
        return 0;
    }
    return xs[semaphore_idx + 1] - xs[semaphore_idx];
}

int solve () {
    // reaching the first semaphore in xs[0] time
    for (int k = 0; k < r_skippable + 1; k++) {
        memo[0][k] = xs[0];
    }
    for (int i = 0; i < n_lights - 1; i++) {
        for (int k = 0; k < r_skippable + 1; k++) {
            memo[(i + 1) % 2][k] = INT_MAX >> 1;
        }
        int dist = dist_to_next(i);
        // we're at the semaphore at distance x
        for (int already_skipped = 0; already_skipped < r_skippable + 1; already_skipped++) {
            // we've already skipped already_skipped semaphores
            int elapsed_time = memo[i % 2][already_skipped];

            if (elapsed_time % (2 * t_half_period) >= t_half_period) {
                // wait for green
                int wait_for_green = 2 * t_half_period - elapsed_time % (2 * t_half_period);
                int time_by_waiting = elapsed_time + dist + wait_for_green;
                memo[(i + 1) % 2][already_skipped] = min(memo[(i + 1) % 2][already_skipped], time_by_waiting);
                // don't wait for green
                if (already_skipped < r_skippable) {
                    int time_by_skipping = elapsed_time + dist;
                    memo[(i + 1) % 2][already_skipped + 1] = min(memo[(i + 1) % 2][already_skipped + 1], time_by_skipping);
                }
            }
            else {
                // already green
                int time_by_waiting = elapsed_time + dist;
                memo[(i + 1) % 2][already_skipped] = min(memo[(i + 1) % 2][already_skipped], time_by_waiting);
            }
        }
    }
    return *min_element(memo[(n_lights + 1) % 2], memo[(n_lights + 1) % 2] + r_skippable + 1);
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    read_input();
    cout << solve() << "\n";
}