#include <bits/stdc++.h>
#define MAXN 500005

using namespace std;

int n_nodes;
int wages[MAXN];
int fenwick[MAXN];
vector<int> graph[MAXN];

int get_wage (int node) {
    return wages[node];
}

void dfs (int node, int am) {
    wages[node] += am;
    for (auto j: graph[node]) {
        dfs(j, am);
    }
}

void update_wages (int node, int am) {
    wages[node] -= am;
    dfs(node, am);
}

int main () {
    int m_queries;
    cin >> n_nodes >> m_queries;
    cin >> wages[0];
    for (int i = 1; i < n_nodes; i++) {
        int parent;
        cin >> wages[i] >> parent;
        parent--;
        graph[parent].push_back(i);
    }

    for (int q = 0; q < m_queries; q++) {
        char command;
        cin >> command;
        if (command == 'p') {
            // change wages of children
            int node, am;
            cin >> node >> am;
            node--;
            update_wages(node, am);
        } else {
            // query wage
            int node;
            cin >> node;
            node--;
            cout << get_wage(node) << "\n";
        }
    }
}
