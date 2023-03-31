#include <bits/stdc++.h>
#define MAXN 500005

using namespace std;

int n_nodes;
int wages[MAXN];
int visit_start[MAXN];
int visit_end[MAXN];
vector<int> graph[MAXN];
int fenwick[MAXN];

void fenwick_update (int i, int am) {
    i++;
    while (i < MAXN) {
        fenwick[i] += am;
        i += (i & (-i));
    }
}

int fenwick_sum (int i) {
    i++;
    int s = 0;
    while (i > 0) {
        s += fenwick[i];
        i -= (i & (-i));
    }
    return s;
}

int get_wage (int node) {
    return fenwick_sum(node);
}

void update_wages (int from, int to, int am) {
    // printf("Updating in range [%d, %d] by %d\n", from, to, am`);
    fenwick_update(from, am);
    fenwick_update(to + 1, -am);
    // for (int i = 0; i < n_nodes; i++) {
    //     cout << get_wage(i) << " \n"[i == n_nodes - 1];
    // }
}

void dfs (int node, int &curr_time) {
    visit_start[node] = curr_time++;
    for (auto j: graph[node]) {
        dfs(j, curr_time);
    }
    // keep the same value for the parent to use as end time
    visit_end[node] = curr_time - 1;
}

int main () {
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
    int m_queries;
    cin >> n_nodes >> m_queries;
    cin >> wages[0];
    for (int i = 1; i < n_nodes; i++) {
        int parent;
        cin >> wages[i] >> parent;
        parent--;
        graph[parent].push_back(i);
    }
    int curr_time = 0;
    dfs(0, curr_time);
    for (int i = 0; i < n_nodes; i++) {
        // cout << i + 1 << ": " << visit_start[i] << " -> " << visit_end[i] << "\n";
        update_wages(visit_start[i], visit_start[i], wages[i]);
    }
    // cout << "\n";

    for (int q = 0; q < m_queries; q++) {
        char command;
        cin >> command;
        if (command == 'p') {
            // change wages of children
            int node, am;
            cin >> node >> am;
            node--;
            update_wages(visit_start[node] + 1, visit_end[node], am);
        } else {
            // query wage
            int node;
            cin >> node;
            node--;
            cout << get_wage(visit_start[node]) << "\n";
        }
    }
}
