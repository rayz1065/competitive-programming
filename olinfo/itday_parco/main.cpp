#include <bits/stdc++.h>
#define MAXN 10005
#define MAXT 50505

using namespace std;

typedef long long ll;

ll memo[2][MAXT][2];

bool is_area_start[MAXN];
int attractions_duration[MAXN];
int attractions_fun[MAXN];

ll visita(int n_areas, int enter_area_time, int max_time,
          vector<int> areas_attractions,
          vector<vector<int>> areas_attractions_duration,
          vector<vector<int>> areas_attractions_fun) {
    int n = 0;
    for (int i = 0; i < areas_attractions.size(); i++) {
        is_area_start[n] = true;
        for (int j = 0; j < areas_attractions[i]; j++) {
            attractions_duration[n] = areas_attractions_duration[i][j];
            attractions_fun[n] = areas_attractions_fun[i][j];
            n += 1;
        }
    }

    for (int i = 0; i < 2; i++) {  // bad states
        for (int t = max_time + 1; t < MAXT; t++) {
            memo[i][t][0] = memo[i][t][1] = LLONG_MIN >> 1;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int t = max_time; t >= 0; t--) {
            memo[i % 2][t][1] =
                max(memo[(i + 1) % 2][t][!is_area_start[i + 1]],
                    memo[(i + 1) % 2][t + attractions_duration[i]]
                        [!is_area_start[i + 1]] +
                        attractions_fun[i]);
            memo[i % 2][t][0] = max(memo[(i + 1) % 2][t][0],
                                    memo[i % 2][t + enter_area_time][1]);
        }
    }

    return memo[0][0][0];
}
