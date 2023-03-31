#include <bits/stdc++.h>
#define MAXN 1005
#define MAXK 80

using namespace std;

struct Branch {
    int to;
    int w_bus;
    int w_walk;
    int vol; // volounteers
};
int n_start, n_end, n_nodes, k_tickets, t_maxtime;
vector<Branch> graph[MAXN];
int dist[MAXN][MAXK];

bool can_reach (int vol_max) {
    for (int i = 0; i < n_nodes; i++) {
        fill(dist[i], dist[i] + k_tickets + 1, t_maxtime + 1);
    }
    set<pair<int, pair<int, int>>> ff;
    ff.insert({ dist[n_start][k_tickets] = 0, { n_start, k_tickets } });
    while (!ff.empty()) {
        auto curr = ff.begin()->second;
        ff.erase(ff.begin());
        int node = curr.first;
        int tickets = curr.second;
        for (auto &b: graph[node]) {
            int new_dist_w = dist[node][tickets] + b.w_walk, new_dist_b = dist[node][tickets] + b.w_bus;
            if (b.vol <= vol_max && dist[b.to][tickets] > new_dist_w) {
                if (b.to == n_end) {
                    return true;
                }
                dist[b.to][tickets] = new_dist_w;
                ff.insert({ new_dist_w, { b.to, tickets }});
            }
            if (tickets > 0 && dist[b.to][tickets - 1] > new_dist_b) {
                dist[b.to][tickets - 1] = new_dist_b;
                if (b.to == n_end) {
                    return true;
                }
                ff.insert({ new_dist_b, { b.to, tickets - 1 }});
            }
        }
    }
    return false;
}

int avoid_volunteers(int subtask, int N, int M, int K, int S, int E, int T, int A[], int B[], int W[], int P[], int V[]) {
    n_start = S, n_end = E, n_nodes = N, k_tickets = K, t_maxtime = T;
    for (int i = 0; i < M; i++) {
        graph[A[i]].push_back({ B[i], P[i], W[i], V[i] });
        graph[B[i]].push_back({ A[i], P[i], W[i], V[i] });
    }
    sort(V, V + M);

    int l = 0, r = M - 1, sol = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (can_reach(V[mid])) {
            sol = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (sol == 0 && (V[0] == 0 || can_reach(0))) {
        return 0;
    } else if (sol == -1) {
        return sol;
    }
    return V[sol];
}
