#include <bits/stdc++.h>
#define MAXX 500005

using namespace std;

int join_at_time[MAXX];

vector<int> cucina(int n_people, int k_queue, int x_end, vector<int> h_times) {
    vector<int> sol(x_end + 1);

    for (auto t: h_times) {
        join_at_time[t]++;
    }

    int available_spots = 0;
    for (int t = x_end - 1; t >= 0; t--) {
        available_spots = min(available_spots + 1, k_queue);
        sol[t] = sol[t + 1];
        if (join_at_time[t] > 0) {
            // new people enter the queue, one served immediately
            int joining = min(join_at_time[t], available_spots);
            available_spots -= joining;
            sol[t] += joining;
        }
    }

    sol.resize(x_end);

    return sol;
}
