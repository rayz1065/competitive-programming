#include <bits/stdc++.h>
#define MAXN 2505
#define MAXM 5005
#define NINF (LLONG_MIN >> 1)

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN], rev_graph[MAXN];
tuple<int, int, int> edges[MAXM];
bool done[MAXN];
ll best_score[MAXN];
bool path_to_end[MAXN];
bool path_from_start[MAXN];

void find_paths_from_start(int node) {
    if (path_from_start[node]) {
        return;
    }
    path_from_start[node] = true;
    for (auto i : graph[node]) {
        find_paths_from_start(i);
    }
}

void find_paths_to_end(int node) {
    if (path_to_end[node]) {
        return;
    }
    path_to_end[node] = true;
    for (auto i : rev_graph[node]) {
        find_paths_to_end(i);
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
        edges[i] = {u, v, w};
        rev_graph[v].push_back(u);
        graph[u].push_back(v);
    }

    find_paths_to_end(n - 1);
    find_paths_from_start(0);
    fill(best_score, best_score + n, NINF);
    best_score[0] = 0;

    bool improves = true;
    for (int i = 0; i < n + 5 && improves; i++) {
        improves = false;
        for (int j = 0; j < m; j++) {
            int u, v, w;
            tie(u, v, w) = edges[j];
            ll new_score = best_score[u] + w;
            if (new_score > best_score[v] && path_to_end[v] &&
                path_from_start[u]) {
                improves = true;
                best_score[v] = new_score;
            }
        }
    }

    if (improves) {
        cout << "-1\n";
        return 0;
    }
    cout << best_score[n - 1] << "\n";
}
