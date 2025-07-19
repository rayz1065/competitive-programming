#include <bits/stdc++.h>
#define MAXN 100005
#define INF (LLONG_MAX >> 1)

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> graph[MAXN];
ll distances[2][MAXN];

ll solve() {
    set<pair<ll, pair<bool, int>>> ff;
    for (int i = 0; i < 2; i++) {
        fill(distances[i], distances[i] + n, INF);
    }
    ff.insert({distances[0][0] = 0, {0, 0}});

    while (!ff.empty()) {
        auto curr = ff.begin();
        bool used_discount;
        ll dist = curr->first;
        int node;
        tie(used_discount, node) = curr->second;
        ff.erase(curr);
        if (dist > distances[used_discount][node]) {
            continue;
        }

        for (auto [i, w] : graph[node]) {
            ll new_dist = dist + w, new_dist_d = dist + w / 2;
            if (new_dist < distances[used_discount][i]) {
                ff.insert({distances[used_discount][i] = new_dist,
                           {used_discount, i}});
            }
            if (!used_discount && new_dist_d < distances[true][i]) {
                ff.insert({distances[true][i] = new_dist_d, {true, i}});
            }
        }
    }

    return distances[true][n - 1];
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        graph[a].push_back({b, w});
    }

    cout << solve() << "\n";
}
