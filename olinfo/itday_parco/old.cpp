#include <bits/stdc++.h>
#define MAXN 10005
#define MAXT 50005

using namespace std;

typedef long long ll;

ll memo[2][2][MAXT];

struct AttractionEvent {
    int area_id;
    int attraction_id;
} attraction_events[MAXN * 2];

ll visita(int n, int x, int T, vector<int> areas_attractions,
          vector<vector<int>> attractions_duration,
          vector<vector<int>> attractions_fun) {
    int event_count = 0;
    for (int i = 0; i < n; i++) {
        attraction_events[event_count++] = {i, -1};
        for (int j = 0; j < areas_attractions[i]; j++) {
            attraction_events[event_count++] = {i, j};
        }
    }

    for (int event_id = event_count - 1; event_id >= 0; event_id--) {
        int area_id = attraction_events[event_id].area_id;
        int attraction_id = attraction_events[event_id].attraction_id;

        for (int t = 0; t <= T; t++) {
            ll res = memo[(event_id + 1) % 2][0][t];

            if (attraction_id == -1) {
                if (t >= x) {
                    res = max(res, memo[(event_id + 1) % 2][1][t - x]);
                }
            } else {
                res = max(res, memo[(event_id + 1) % 2][1][t]);
                if (t >= attractions_duration[area_id][attraction_id]) {
                    res = max(
                        res,
                        memo[(event_id + 1) % 2][1]
                            [t - attractions_duration[area_id][attraction_id]] +
                            attractions_fun[area_id][attraction_id]);
                }
            }

            memo[event_id % 2][0][t] =
                attraction_id == -1 ? res : memo[(event_id + 1) % 2][0][t];
            memo[event_id % 2][1][t] = res;
        }
    }

    return memo[0][0][T];
}
