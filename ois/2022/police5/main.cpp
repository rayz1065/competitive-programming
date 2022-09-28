#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 10005

using namespace std;

int n_nodes, m_branches, t_explosion;

struct Branch {
    int to;
    int cost;
    bool explodes;
};
vector<Branch> graph[MAXN];
int dist[MAXN];

void djikstra () {
    set<pair<int, int>> ff;
    fill(dist, dist + n_nodes, INT_MAX >> 1);
    ff.insert({ 0, 0 });
    dist[0] = 0;

    while (!ff.empty()) {
        auto curr = ff.begin();
        ff.erase(curr);
        int node = curr->second;

        for (auto branch: graph[node]) {
            int reached_at = dist[node] + branch.cost;
            bool can_reach = !branch.explodes || reached_at <= t_explosion;
            // cout << node << " can go to " << branch.to << " " << reached_at << " " << can_reach << "\n";
            if (can_reach && reached_at < dist[branch.to]) {
                ff.insert({ reached_at, branch.to });
                dist[branch.to] = reached_at;
            }
        }
    }
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n_nodes >> m_branches >> t_explosion;
    for (int i = 0; i < m_branches; i++) {
        int a, b, c;
        bool e;
        cin >> a >> b >> c >> e;
        graph[a].push_back({ b, c, e });
        // graph[b].push_back({ a, c, e }); // woops, directional roads
    }

    djikstra();
    if (dist[n_nodes - 1] == INT_MAX >> 1) {
        cout << -1 << "\n";
    } else {
        cout << dist[n_nodes - 1] << "\n";
    }
}
