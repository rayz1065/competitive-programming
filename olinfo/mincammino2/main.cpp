#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

typedef long long ll;

vector<pair<int, int>> graph[MAXN];
ll distances[MAXN];

void mincammino(int n, int m, vector<int> branch_x, vector<int> branch_y,
                vector<int> branch_w, vector<ll>& res) {
    for (int i = 0; i < m; i++) {
        graph[branch_x[i]].push_back({branch_y[i], branch_w[i]});
    }

    fill(distances, distances + MAXN, LLONG_MAX >> 1);
    distances[0] = 0;
    set<pair<ll, int>> ff;
    ff.insert({0, 0});

    while (!ff.empty()) {
        auto curr = ff.begin();
        int node = curr->second;
        ll dist = curr->first;
        ff.erase(curr);
        if (dist > distances[node]) {
            continue;
        }

        for (auto j : graph[node]) {
            ll new_dist = dist + j.second;
            if (new_dist < distances[j.first]) {
                distances[j.first] = new_dist;
                ff.insert({new_dist, j.first});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        res[i] = distances[i] < (LLONG_MAX >> 1) ? distances[i] : -1;
    }
}
