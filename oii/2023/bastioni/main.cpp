#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 300005

using namespace std;

int arrampicate(int n, string doors) {
    int required_visits = 0;
    bool used_left_door = false;
    bool used_right_door = false;
    bool visited_any = false;

    for (int i = 0;; i++) {
        // visit room i
        visited_any = true;
        if (i == n) {
            // the last room must be visited by itself if !visited_any
            break ;
        }

        char door = doors[i];
        bool is_right_door = door == '>' || door == '?';
        bool is_left_door = door == '<' || door == '?';

        if (door == '#' || (is_left_door && used_right_door) || (is_right_door && used_left_door)) {
            // cannot continue further
            required_visits += 1;
            visited_any = used_left_door = used_right_door = false;
            continue;
        }

        used_right_door |= is_right_door;
        used_left_door |= is_left_door;
    }

    if (visited_any) {
        required_visits += 1;
    }

    return required_visits;
}
