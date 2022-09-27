#include <bits/stdc++.h>
#define MAXN 10005
#define MAXC 105
#pragma GCC optimize("O3")

using namespace std;

int n_tasks, c_skips;
int parent[MAXN];
vector<int> graph[MAXN];
int cost[MAXN];
int root;
long long memo[MAXN][MAXC];
vector<int> toposort;

long long solve (int node, int skips) {
    // repartition c into the children in a greedy way
    if (memo[node][skips] != -1) {
        return memo[node][skips];
    }

    if (graph[node].size() == 0) {
        // base case
        if (skips > 0) {
            return memo[node][skips] = 0;
        }
        return memo[node][skips] = cost[node];
    }

    vector<int> partitions(graph[node].size(), 0);
    set<pair<long long, int>> curr_costs; // priority queue
    for (int j = 0; j < graph[node].size(); j++) {
        // costs without any cuts
        int other_node = graph[node][j];
        curr_costs.insert({ -solve(other_node, partitions[j]), j });
    }
    // the cost by not skipping any node (skips == 0)
    long long s = cost[node] - curr_costs.begin()->first;
    memo[node][0] = s;

    for (int i = 1; i <= skips; i++) {
        // use i of the skips
        // try to skip the current node first
        s = min(s, -curr_costs.begin()->first);
        // increment the number of cuts, each time to the most expensive
        int j = curr_costs.begin()->second;
        int other_node = graph[node][j];
        curr_costs.erase(curr_costs.begin());
        partitions[j]++;
        curr_costs.insert({ -solve(other_node, partitions[j]), j });

        // try skipping the current node
        s = min(s, cost[node] - curr_costs.begin()->first);
        memo[node][i] = s;
    }

    // printf("memo[%d][%d] = %d\n", node, skips, s);
    return memo[node][skips];
}

void find_toposort (int node) {
    for (auto j: graph[node]) {
        find_toposort(j);
    }
    toposort.push_back(node);
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n_tasks >> c_skips;
    for (int i = 0; i < n_tasks; i++) {
        cin >> parent[i] >> cost[i];
        if (parent[i] == -1) {
            root = i;
        } else {
            graph[parent[i]].push_back(i);
        }
    }

    for (int i = 0; i < n_tasks; i++) {
        fill(memo[i], memo[i] + c_skips + 1, -1);
    }
    find_toposort(root);
    for (auto i: toposort) {
        // call them in topological order
        solve(i, c_skips);
    }

    cout << solve(root, c_skips) << "\n";
}
