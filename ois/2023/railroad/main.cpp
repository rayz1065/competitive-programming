#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 300005

using namespace std;

typedef long long ll;

int n_nodes;
int m_branches;
struct Branch {
    int a;
    int b;
    int c;
} branches[MAXM];
vector<pair<int, int>> graph[MAXN];
ll dist_from_start[MAXN];
ll dist_to_end[MAXN];
bool on_best_path[MAXN];

void djikstra (int node, ll *dist) {
    fill(dist, dist + n_nodes, LLONG_MAX >> 1);
    dist[node] = 0;
    set<pair<ll, int>> ff;
    ff.insert({ 0, node });
    while (!ff.empty()) {
        node = ff.begin()->second;
        ff.erase(ff.begin());
        for (auto b: graph[node]) {
            ll new_dist = dist[node] + b.second;
            if (new_dist < dist[b.first]) {
                ff.insert({ dist[b.first] = new_dist, b.first });
            }
        }
    }
}

void mark_best_path () {
    int node = 0;
    ll target_dist = dist_from_start[n_nodes - 1];
    while (node != n_nodes - 1) {
        on_best_path[node] = true;
        for (auto j: graph[node]) {
            if (dist_from_start[node] + j.second + dist_to_end[j.first] == target_dist) {
                node = j.first;
                break ;
            }
        }
    }
    assert(node == n_nodes - 1);
    on_best_path[node] = true;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n_nodes >> m_branches;
    for (int i = 0; i < m_branches; i++) {
        cin >> branches[i].a >> branches[i].b >> branches[i].c;
        graph[branches[i].a].push_back({ branches[i].b, branches[i].c });
        graph[branches[i].b].push_back({ branches[i].a, branches[i].c });
    }
    djikstra(0, dist_from_start);
    djikstra(n_nodes - 1, dist_to_end);
    mark_best_path();
    ll target_dist = dist_from_start[n_nodes - 1];
    ll best = INT_MAX >> 1;
    for (int i = 0; i < m_branches; i++) {
        auto b = branches[i];
        if (on_best_path[b.a] && on_best_path[b.b]) {
            // already on best path
            continue ;
        }
        ll first_dist = dist_from_start[b.a] + dist_to_end[b.b] + b.c;
        ll second_dist = dist_from_start[b.b] + dist_to_end[b.a] + b.c;
        ll diff = min(first_dist, second_dist) - target_dist + 1;
        if (diff <= b.c) {
            best = min(best, diff);
        }
    }
    cout << (best == INT_MAX >> 1 ? -1 : best) << "\n";
}
