#include <bits/stdc++.h>
#pragma GCC optimize("O3")

void fastin (int &v) {
    v = 0;
    char c = getchar_unlocked();
    for (; c >= '0'; c = getchar_unlocked()) {
        v = v * 10 + c - '0';
    }
}

#define MAXN 10005
#define MAXM 100005

using namespace std;

// input data
int n_nodes, m_branches;
typedef struct Branch {
    int a;
    int b;
    bool flipped;
    bool visited;
} Branch;

vector<pair<int, int>> graph[MAXN]; // branch_id and destination
Branch branches[MAXM];
bool visited[MAXN];
int dfs_used_branch[MAXN]; // what branch was used in the dfs

int dfs_find_loop (int node, int from) {
    if (visited[node]) {
        // found the start of the loop
        return node;
    }
    visited[node] = true;
    for (auto j: graph[node]) {
        int to = j.first;
        if (to != from) {
            dfs_used_branch[node] = j.second;
            return dfs_find_loop(to, node);
        }
    }
    assert(false);
}

void orient_branch (int branch_id, int from) {
    Branch *branch = &branches[branch_id];
    // assert(!branch->visited);
    branch->visited = true;
    branch->flipped = branch->a != from; // it's flipped if it goes from b to a
}

void find_loop () {
    // find a loop and visit it, orienting the branches
    fill(visited, visited + n_nodes, false);
    int starting_node = dfs_find_loop(0, -1);

    fill(visited, visited + n_nodes, false);
    int node = starting_node;
    do {
        int branch_id = dfs_used_branch[node];
        Branch branch = branches[branch_id];
        orient_branch(branch_id, node);
        node = branch.a == node ? branch.b : branch.a; // the other extreme
        visited[node] = true; // mark all the nodes as visited
        // printf("part of loop %d\n", node);
    } while(node != starting_node);
}

void dfs (int node) {
    if (visited[node]) {
        return ;
    }
    visited[node] = true;
    for (auto j: graph[node]) {
        Branch branch = branches[j.second];
        if (!branch.visited) {
            orient_branch(j.second, node);
        }
        dfs(j.first);
    }
}

void visit_all_nodes () {
    // visit every node
    for (int i = 0; i < n_nodes; i++) {
        if (visited[i]) {
            // revisit the node
            visited[i] = false;
            dfs(i);
        }
    }
    // for (int i = 0; i < n_nodes; i++) {
    //     assert (visited[i]);
    // }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    fastin(n_nodes);
    fastin(m_branches);
    for (int i = 0; i < m_branches; i++) {
        fastin(branches[i].a);
        fastin(branches[i].b);
        graph[branches[i].a].push_back({ branches[i].b, i });
        graph[branches[i].b].push_back({ branches[i].a, i });
    }

    // insert your code here
    find_loop();
    visit_all_nodes();

    // print the result
    for (int i = 0; i < m_branches; i++) {
        int a = branches[i].a, b = branches[i].b;
        if (branches[i].flipped) {
            swap(a, b);
        }
        cout << a << " " << b << "\n";
    }
    return 0;
}
