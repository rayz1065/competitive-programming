#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<pii> rev_graph[MAXN];
ll distances[MAXN];
pair<int, ll> parent[MAXN];
bool mistake_used[MAXN];

vector<int> station_mistake;
vector<int> station_mistake_t;

void rev_dijkstra() {
    int node = n - 1;
    ll dist = 0;
    parent[node] = {-1, LLONG_MAX >> 1};

    fill(distances, distances + n, LLONG_MAX >> 1);
    distances[node] = dist;

    set<pair<ll, int>> ff;
    ff.insert({distances[node], node});

    while (!ff.empty()) {
        auto curr = ff.begin();
        ff.erase(curr);
        node = curr->second;
        dist = curr->first;
        if (dist > distances[node]) {
            continue;
        }

        for (auto j : rev_graph[node]) {
            ll new_dist = dist + j.second;
            if (new_dist < distances[j.first]) {
                distances[j.first] = new_dist;
                ff.insert({new_dist, j.first});
                parent[j.first] = {node, j.second};
            }
        }
    }
}

pair<int, ll> find_next_mistake(int node) {
    if (node == n - 1 || !mistake_used[node] && station_mistake[node] != -1) {
        return {node, 0};
    }

    auto branch = parent[node];
    auto res = find_next_mistake(branch.first);

    // compress path
    parent[node] = {res.first, res.second + branch.second};

    return parent[node];
}

ll fast_simulate() {
    int node = 0;
    ll res = 0;

    while (node != n - 1) {
        auto next_mistake = find_next_mistake(node);
        node = next_mistake.first;
        res += next_mistake.second;

        if (node != n - 1) {
            mistake_used[node] = true;
            res += station_mistake_t[node];
            node = station_mistake[node];
        }
    }

    return res;
}

ll viaggia(int n, int m, vector<int> branch_a, vector<int> branch_b,
           vector<int> branch_t, vector<int> station_mistake,
           vector<int> station_mistake_t) {
    ::n = n;
    ::station_mistake = station_mistake;
    ::station_mistake_t = station_mistake_t;
    station_mistake[n - 1] = -1;
    station_mistake_t[n - 1] = -1;

    for (int i = 0; i < m; i++) {
        rev_graph[branch_b[i]].push_back({branch_a[i], branch_t[i]});
    }

    rev_dijkstra();

    return fast_simulate();
}
