#include <bits/stdc++.h>
#define MAXN 2005

using namespace std;

typedef long long ll;

ll fastin() {
    ll v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int node_count;
unordered_map<ll, int> location_nodes;
ll node_locations[MAXN];
int self_loops[MAXN];
vector<int> graph[MAXN];
ll memo[MAXN][MAXN];

int get_node(ll location, bool create) {
    auto res = location_nodes.find(location);
    if (res != location_nodes.end()) {
        return res->second;
    } else if (!create) {
        return -1;
    }

    int node = node_count++;
    node_locations[node] = location;
    location_nodes[location] = node;
    return node;
}

ll solve(int node, int trips) {
    // compute for each node, with exactly "trips" trips the best result
    if (memo[node][trips] != 0) {
        return memo[node][trips] - 2;
    } else if (trips == 0) {
        return node_locations[node];
    }

    ll best = self_loops[node] >= trips ? node_locations[node] : -1;
    for (int taken = 0; taken <= self_loops[node] && trips - taken - 1 >= 0; taken++) {
        for (auto j: graph[node]) {
            best = max(best, solve(j, trips - taken - 1));
        }
    }

    // offset by 2 to allow storing -1
    memo[node][trips] = best + 2;
    return best;
}

ll find_path(int node, int min_branches, int max_branches) {
    ll best = -1;
    for (int trips = min_branches; trips <= max_branches; trips++) {
        best = max(best, solve(node, trips));
    }

    return best;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n_trips = fastin();
    for (int i = 0; i < n_trips; i++) {
        ll l = fastin(), r = fastin();
        int node_l = get_node(l, true), node_r = get_node(r, true);
        if (node_l == node_r) {
            self_loops[node_l] += 1;
        } else {
            graph[node_l].push_back(node_r);
        }
    }

    int q_queries = fastin();
    while (q_queries--) {
        ll location = fastin();
        int min_branches = fastin(), max_branches = fastin();
        int node = get_node(location, false);

        ll res;
        if (node == -1) {
            res = min_branches == 0 ? location : -1;
        } else {
            res = find_path(node, min_branches, max_branches);
        }

        cout << res << " \n"[q_queries == 0];
    }
}
