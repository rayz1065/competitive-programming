#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

vector<pair<int, int>> graph[MAXN];
int dist[MAXN];
int n_nodes;

void dijkstra () {
    set<pair<int, int>> ff;
    fill(dist, dist + n_nodes, -1);
    dist[0] = 0;
    ff.insert({ 0, 0 });

    while (!ff.empty()) {
        auto item = ff.begin();
        ff.erase(item);
        int node = item->second;

        if (dist[node] < item->first) {
            continue ;
        }

        for (auto j: graph[node]) {
            int target_node = j.first;
            int new_dist = dist[node] + j.second;
            if (new_dist < dist[target_node] || dist[target_node] == -1) {
                dist[target_node] = new_dist;
                ff.insert({ new_dist, target_node });
            }
        }
    }
}

void mincammino(int n_nodes, int m_branches, vector<int> X, vector<int> Y, vector<int> P, vector<int> &D) {
    ::n_nodes = n_nodes;

    for (int i = 0; i < m_branches; i++) {
        graph[X[i]].push_back({ Y[i], P[i] });
    }

    dijkstra();

    for (int i = 0; i < n_nodes; i++) {
        D[i] = dist[i];
    }
}
