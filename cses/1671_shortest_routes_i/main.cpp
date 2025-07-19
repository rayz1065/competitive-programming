#include <bits/stdc++.h>
#define MAXN 100005
#define INF (LLONG_MAX >> 1)

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> graph[MAXN];

ll distances[MAXN];

void djikstra(int start) {
    set<pair<ll, int>> ff;
    fill(distances, distances + n, INF);
    ff.insert({distances[start] = 0, start});

    while (!ff.empty()) {
        ll dist;
        int node;
        auto curr = *ff.begin();
        tie(dist, node) = curr;
        ff.erase(curr);
        if (distances[node] < dist) {
            continue;
        }

        for (auto [i, w] : graph[node]) {
            ll new_dist = distances[node] + w;
            if (new_dist < distances[i]) {
                ff.insert({distances[i] = new_dist, i});
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].push_back({v, w});
    }

    djikstra(0);

    for (int i = 0; i < n; i++) {
        cout << distances[i] << " \n"[i + 1 == n];
    }
}
