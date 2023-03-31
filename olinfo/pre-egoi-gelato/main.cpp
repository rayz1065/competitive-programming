#include <bits/stdc++.h>

using namespace std;

int presta(int n_friends, int cost, vector<int> friends) {
    int lb = 0, ub = n_friends - 1;
    int collected = 0;
    while (lb < ub - 1) {
        // divide the search space
        int mid = (lb + ub) / 2;
        nth_element(friends.begin() + lb,
            friends.begin() + mid,
            friends.begin() + ub + 1);
        // sum up all the next elements
        int sum = 0;
        for (int i = mid; i <= ub; i++) {
            sum += friends[i];
        }
        // cout << "from " << mid << " to " << ub << " collects " << sum << "\n";

        if (collected + sum <= cost) {
            // collect and move further to the left
            collected += sum;
            ub = mid - 1;
        } else {
            // don't collect yet, move to the right
            lb = mid;
        }
    }

    collected = 0;
    int req_friends = 0;
    for (int i = n_friends - 1; i >= 0 && collected < cost; i--) {
        collected += friends[i];
        req_friends++;
    }

    return req_friends;
}
