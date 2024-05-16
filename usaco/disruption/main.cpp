#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;

using SolutionT = set<pair<int, int>> *;

int n;
vector<pair<int, int>> graph[MAXN];        // id, target
vector<pair<int, int>> extra_edges[MAXN];  // weight, id

int solutions[MAXN];

bool sort_by_size(SolutionT &a, SolutionT &b) { return a->size() < b->size(); }

SolutionT dfs(int node, int parent) {
    // returns (weight, id) of available replacements
    vector<SolutionT> children;
    children.reserve(graph[node].size());

    for (auto [id, j] : graph[node]) {
        if (j == parent) {
            continue;
        }

        auto sub_solution = dfs(j, node);
        children.push_back(sub_solution);

        if (!sub_solution->empty()) {
            solutions[id] = sub_solution->begin()->first;
        }
    }

    sort(children.begin(), children.end(), sort_by_size);

    SolutionT res;

    if (!children.empty()) {
        res = children.back();
        children.pop_back();
    } else {
        res = new set<pair<int, int>>();
    }

    for (auto sub_solution : children) {
        for (auto edge : *sub_solution) {
            if (res->find(edge) == res->end()) {
                res->insert(edge);
            } else {
                res->erase(edge);
            }
        }
    }

    for (auto edge : extra_edges[node]) {
        if (res->find(edge) == res->end()) {
            res->insert(edge);
        } else {
            res->erase(edge);
        }
    }

    for (auto sub_solution : children) {
        delete sub_solution;
    }

    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("disrupt.in", ios::in);
    cout.open("disrupt.out", ios::out);
#endif
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back({i, b});
        graph[b].push_back({i, a});
    }

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        extra_edges[a].push_back({w, i});
        extra_edges[b].push_back({w, i});
    }

    fill(solutions, solutions + n, -1);

    dfs(0, 0);

    for (int i = 0; i < n - 1; i++) {
        cout << solutions[i] << "\n";
    }
}
