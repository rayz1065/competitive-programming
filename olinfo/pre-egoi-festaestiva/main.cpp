#include <bits/stdc++.h>

using namespace std;

int organizza(int n_friends, int party_lb, int party_ub, vector<int> vacation_from, vector<int> vacation_to){
    sort(vacation_from.begin(), vacation_from.end());
    sort(vacation_to.begin(), vacation_to.end());
    for (int i = 0; i < n_friends; i++) {
        // make the end exclusive
        vacation_to[i]++;
    }
    vacation_from.push_back(INT_MAX >> 1);
    vacation_to.push_back(INT_MAX >> 1);

    int from_idx = 0, to_idx = 0;

    // skip all the ones before the window
    while (from_idx < n_friends && vacation_from[from_idx] <= party_lb) {
        from_idx++;
    }
    while (to_idx < n_friends && vacation_to[to_idx] <= party_lb) {
        to_idx++;
    }
    int best_sol = n_friends - from_idx + to_idx;
    int current_day = party_lb;

    while (from_idx < n_friends || to_idx < n_friends) {
        int next_change = min(vacation_from[from_idx], vacation_to[to_idx]);
        current_day = next_change;
        if (current_day > party_ub) {
            break ;
        }

        while (vacation_from[from_idx] == current_day) {
            from_idx++;
        }
        while (vacation_to[to_idx] == current_day) {
            to_idx++;
        }
        // cout << "on day " << current_day << " there are " << currently_present << " friends\n";
        // if the day is contained within the bounds...
        best_sol = max(best_sol, n_friends - from_idx + to_idx);
    }
    return best_sol;
}