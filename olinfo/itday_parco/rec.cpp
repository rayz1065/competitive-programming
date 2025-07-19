#include <bits/stdc++.h>
#define MAXN 10005
#define MAXT 50005

using namespace std;

typedef long long ll;

// ll memo[MAXN][MAXT][2];
ll memo[2][MAXT][2];

int n;
int enter_area_time;
int max_time;
int area_ids[MAXN];
int attractions_duration[MAXN];
int attractions_fun[MAXN];

// ll solve(int i, int t, bool flag) {
//     if (i == n || t == max_time) {
//         return 0;
//     } else if (memo[i][t][flag]) {
//         return memo[i][t][flag] - 1;
//     }

//     ll best = solve(i + 1, t, flag && area_ids[i + 1] == area_ids[i]);
//     if (!flag && t + enter_area_time <= max_time) {
//         best = max(best, solve(i, t + enter_area_time, flag + 1));
//     }
//     if (flag && t + attractions_duration[i] <= max_time) {
//         best = max(best, solve(i + 1, t + attractions_duration[i],
//                                area_ids[i + 1] == area_ids[i]) +
//                              attractions_fun[i]);
//     }
//     memo[i][t][flag] = best + 1;
//     return best;
// }

ll visita(int n_areas, int enter_area_time, int max_time,
          vector<int> areas_attractions,
          vector<vector<int>> attractions_duration,
          vector<vector<int>> attractions_fun) {
    ::enter_area_time = enter_area_time;
    ::max_time = max_time;

    int attraction_id = 0;
    for (int i = 0; i < areas_attractions.size(); i++) {
        for (int j = 0; j < areas_attractions[i]; j++) {
            area_ids[attraction_id] = i;
            ::attractions_duration[attraction_id] = attractions_duration[i][j];
            ::attractions_fun[attraction_id] = attractions_fun[i][j];
            attraction_id += 1;
        }
    }
    area_ids[attraction_id] = areas_attractions.size();
    n = attraction_id;
}
