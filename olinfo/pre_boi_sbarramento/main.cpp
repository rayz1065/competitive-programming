#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n_nodes;
struct Branch {
    int to;
    int cost;
    bool red;
};
vector<Branch> back_graph[MAXN];
bool visited[MAXN];
long long red_dist[MAXN];
long long dist[MAXN];

void find_distances () {
    // start at the end, go towards the start,
    // calculate red and blue distances on the way
    int node = n_nodes - 1;
    set<pair<long long, int>> ff;
    fill(red_dist, red_dist + n_nodes, LLONG_MAX >> 1);
    fill(dist, dist + n_nodes, LLONG_MAX >> 1);
    // fill(visited, visited + n_nodes, false);
    red_dist[node] = dist[node] = 0;
    ff.insert({ dist[node], node });

    while (!ff.empty()) {
        auto curr = ff.begin();
        node = curr->second;
        long long curr_dist = curr->first;
        ff.erase(curr);
        if (visited[node]) {
            continue ;
        }
        if (curr_dist == dist[node] - 1) {
            // trying to visit when setting off the semaphore here
            if (red_dist[node] < dist[node]) {
                // the light will turn red
                dist[node]--;
            } else {
                // the light will not turn red
                ff.insert({ dist[node], node });
                continue ;
            }
        }
        visited[node] = true;
        for (auto branch: back_graph[node]) {
            long long new_dist = dist[node] + branch.cost;
            if (branch.red) {
                // calculate the red distance
                red_dist[branch.to] = min(red_dist[branch.to], new_dist);
            } else if (new_dist < dist[branch.to]) {
                // calculate the new dist and add to visit
                ff.erase({ dist[branch.to], branch.to });
                dist[branch.to] = new_dist;
                ff.insert({ new_dist - 1, branch.to });
            }
        }
    }
}

long long fuggi(int N, int M, vector <int> A, vector <int> B, vector <int> T, vector <int> R){
    ::n_nodes = N;
    for (int i = 0; i < M; i++) {
        back_graph[B[i]].push_back({ A[i], T[i], (bool) R[i] });
    }

    find_distances();
    // for (int i = 0; i < n_nodes; i++) {
    //     printf("%d has dist %lld, red dist %lld\n", i, dist[i], red_dist[i]);
    // }
    return dist[0];
}
