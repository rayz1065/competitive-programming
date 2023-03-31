#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n_nodes;
struct Branch {
    int to;
    int len;
};
vector<Branch> graph[MAXN];
bool is_exit[MAXN];
long long dist[MAXN][2]; // dist[0] best, dist[1] fallback

void dijkstra () {
    set<pair<int, int>> ff;
    for (int i = 0; i < n_nodes; i++) {
        if (!is_exit[i]) {
            dist[i][0] = LLONG_MAX >> 1;
            dist[i][1] = LLONG_MAX >> 1;
        } else {
            ff.insert({ dist[i][1], i });
        }
    }

    while (!ff.empty()) {
        auto curr = ff.begin();
        ff.erase(curr);
        int node = curr->second;
        int curr_dist = dist[node][1];
        if (curr->first != curr_dist) {
            // already visited
            continue ;
        }

        for (auto branch: graph[node]) {
            // try to visit this node
            int new_dist = curr_dist + branch.len;
            if (dist[branch.to][1] > new_dist) {
                dist[branch.to][1] = new_dist;
                if (dist[branch.to][0] > dist[branch.to][1]) {
                    // keep the smallest number first
                    swap(dist[branch.to][0], dist[branch.to][1]);
                }
                // cout << "From " << node << " can reach " << branch.to << " with " << curr_dist << " (" << dist[branch.to][0] << ", " << dist[branch.to][1] << ")\n";
                if (dist[branch.to][1] != (LLONG_MAX >> 1)) {
                    // can visit
                    ff.insert({ dist[branch.to][1], branch.to });
                    // cout << "Can visit " << branch.to << "\n";
                }
            }
        }
    }
}

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
    n_nodes = N;
    // add branches
    for (int i = 0; i < M; i++) {
        int a = R[i][0], b = R[i][1];
        graph[a].push_back({ b, L[i] });
        graph[b].push_back({ a, L[i] });
    }
    for (int i = 0; i < K; i++) {
        is_exit[P[i]] = true;
    }
    dijkstra();
    return dist[0][1];
}
