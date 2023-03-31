#include <bits/stdc++.h>
#define MAXN 10005
#define MAXP 420

using namespace std;

int n, k;
int dist[MAXN][MAXP];
vector<int> graph[MAXN];

int bfs () {
    queue<pair<int, int>> ff;
    dist[0][0] = 0;
    ff.push({ 0, 0 });
    while (!ff.empty()) {
        auto curr = ff.front();
        ff.pop();
        int node = curr.first, p = curr.second;
        // cout << node << "," << p << " -> " << dist[node][p] << "\n";
        for (auto j: graph[node]) {
            int new_dist = dist[node][p] + 1;
            if (dist[j][(p + 1) % MAXP] == (INT_MAX >> 1)) {
                ff.push({ j, (p + 1) % MAXP });
                dist[j][(p + 1) % MAXP] = new_dist;
            }
        }
    }
    int min_dist = INT_MAX >> 1;
    for (int p = 0; p < MAXP; p++) {
        if (dist[n - 1][p] != -1) {
            min_dist = min(min_dist, dist[n - 1][p]);
        }
    }
    if (min_dist == INT_MAX >> 1) return -1;
    return min_dist;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        graph[i].push_back(i); // "wait" edge
    }
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + MAXP, INT_MAX >> 1);
    }
    for (int i = 0; i < k; i++) {
        int period;
        cin >> period;
        for (int j = 0; j < period; j++) {
            int mh;
            cin >> mh;
            for (int k = j; k < MAXP; k += period) {
                dist[mh][k] = -1;
            }
        }
    }

    cout << bfs() << "\n";
}