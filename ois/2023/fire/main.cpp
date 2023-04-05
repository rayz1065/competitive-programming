#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n_nodes;
int edges[MAXN][2];
vector<pair<int, bool>> graph[MAXN];
int memo[MAXN][2];
int s_memo[MAXN];
bool total_sum[MAXN];
pair<int, pair<int, bool>> best_cuts[MAXN][3];

int solve (int edge, bool edge_dire) {
    // cerr << edge << " " << edge_dire << "\n";
    if (memo[edge][edge_dire]) {
        return memo[edge][edge_dire];
    } else if (edge == n_nodes && edge_dire == 0) {
        return 0;
    }
    int node = edges[edge][edge_dire];
    int parent = edges[edge][1 - edge_dire];

    int s = 1;
    int best_cut = 0;

    if (best_cuts[node][0].second.first == -1) {
        // not yet computed, find a list of top 3 cuts
        best_cuts[node][0] = { -1, { edge, 1 - edge_dire }};
        for (auto j: graph[node]) {
            if (j.first == edge) {
                continue ;
            }
            int cut = solve(j.first, j.second);
            s += cut;
            if (cut > best_cuts[node][2].first) {
                best_cuts[node][2] = { cut, j };
            }
            if (best_cuts[node][2].first > best_cuts[node][1].first) {
                swap(best_cuts[node][2], best_cuts[node][1]);
            }
        }
        s_memo[node] = s;
    } else {
        // reconstructs the total sum without needing to iterate through all the edges
        if (best_cuts[node][0].first == -1) {
            // need to compute the cut towards the dfs_parent
            best_cuts[node][0].first = solve(best_cuts[node][0].second.first, best_cuts[node][0].second.second);
        }
        // the cut towards the dfs_parent was not counted, add it in
        s = s_memo[node] + best_cuts[node][0].first;
        // the cut towards the current edge was already counted, remove it
        s -= solve(edge, 1 - edge_dire);
    }
    // take the best cut which is not the parent
    for (int j = 0; j < 3; j++) {
        if (best_cuts[node][j].second.first != edge) {
            best_cut = max(best_cut, best_cuts[node][j].first);
        }
    }
    s -= best_cut;
    return memo[edge][edge_dire] = s;
}

int main () {
    cin >> n_nodes;
    for (int i = 0; i < n_nodes - 1; i++) {
        cin >> edges[i][0] >> edges[i][1];
        graph[edges[i][0]].push_back({ i, 1 });
        graph[edges[i][1]].push_back({ i, 0 });
    }
    for (int i = 0; i < n_nodes; i++) {
        for (int j = 0; j < 3; j++) {
            best_cuts[i][j].second.first = -1;
        }
    }

    edges[n_nodes][0] = -1;
    for (int i = 0; i < n_nodes; i++) {
        memo[n_nodes][1] = 0;
        edges[n_nodes][1] = i;
        cout << solve(n_nodes, 1) << " \n"[i + 1 == n_nodes];
    }
}
