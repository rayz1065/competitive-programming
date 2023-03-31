#include <bits/stdc++.h>
#define MAXN 35
#define BREATH 20

using namespace std;
int n, m, c, k;
bool has_air[MAXN];
int dist[MAXN][BREATH + 1];
vector<pair<int, int>> graph[MAXN];

void djikstra () {
    set<pair<int, pair<int, int>>> ff;
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + BREATH + 1, INT_MAX >> 1);
    }
    ff.insert({ dist[0][BREATH] = 0, { 0, BREATH } });
    while (!ff.empty()) {
        auto node_info = ff.begin()->second;
        int node = node_info.first, breath = node_info.second;
        ff.erase(ff.begin());
        if (has_air[node]) {
            dist[node][BREATH] = min(dist[node][BREATH], dist[node][breath]);
            breath = BREATH;
        }
        for (auto b: graph[node]) {
            int new_dist = dist[node][breath] + b.second;
            int new_breath = breath - b.second;
            if (new_breath >= 0 && new_dist < dist[b.first][new_breath]) {
                ff.insert({ new_dist, { b.first, new_breath } });
                dist[b.first][new_breath] = new_dist;
            }
        }
    }
}

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> n >> m >> c >> k;
    c--;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x--;
        has_air[x] = true;
    }
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        graph[x].push_back({ y, w });
        graph[y].push_back({ x, w });
    }

    djikstra();
    int sol = *min_element(dist[c], dist[c] + BREATH + 1);
    cout << ((sol == INT_MAX >> 1) ? -1 : sol) << "\n";
}