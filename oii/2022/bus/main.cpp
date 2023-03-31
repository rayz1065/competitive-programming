#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n_graph_nodes;
int n_nodes;
int exit_nodes[MAXN];
int corresponding_nodes[MAXN * 3];
vector<pair<int, int>> graph[MAXN * 4];
int dist[MAXN * 4];

void dijkstra () { // can convert to bfs
    int node = 0;
    set<pair<int, int>> ff;
    fill(dist, dist + n_graph_nodes, INT_MAX >> 1);
    ff.insert({ dist[node] = -1, node });

    while (!ff.empty()) {
        auto curr = ff.begin();
        node = curr->second;
        // cout << curr->first << " (" << corresponding_nodes[node] << ")\t" << node << "\n";
        ff.erase(curr);
        for (auto j: graph[node]) {
            int new_dist = dist[node] + j.second;
            int new_node = j.first;
            if (dist[new_node] > new_dist) {
                dist[new_node] = new_dist;
                ff.insert({ new_dist, new_node });
            }
        }
    }
}

int pianifica(int n_nodes, int l_lines, vector<vector<int>> f_lines_stops) {
    ::n_nodes = n_nodes;
    for (int i = 0; i < n_nodes; i++) {
        corresponding_nodes[i] = n_graph_nodes++;
    }

    for (int i = 0; i < l_lines; i++) {
        int a = n_graph_nodes++;
        auto stop_a = f_lines_stops[i][0];
        for (int j = 1; j < f_lines_stops[i].size(); j++) {
            auto stop_b = f_lines_stops[i][j];
            int b = n_graph_nodes++;
            corresponding_nodes[a] = stop_a;
            corresponding_nodes[b] = stop_b;
            graph[a].push_back({ b, 0 });
            a = b;
            stop_a = stop_b;
        }
    }
    for (int i = n_nodes; i < n_graph_nodes; i++) {
        auto bus_stop = corresponding_nodes[i];
        // taking a bus costs 1
        graph[bus_stop].push_back({ i, 1 });
        // leaving the bus is free
        graph[i].push_back({ bus_stop, 0 });
    }

    dijkstra();
    if (dist[n_nodes - 1] == INT_MAX >> 1) {
        return -1;
    }
    return dist[n_nodes - 1];
}
