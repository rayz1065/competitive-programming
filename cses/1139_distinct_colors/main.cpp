#include <bits/stdc++.h>

#include <unordered_set>
#define MAXN 200005

using namespace std;

int n;
int colors[MAXN];
vector<int> graph[MAXN];
int results[MAXN];

unordered_set<int>* solve(int node, int parent) {
    vector<unordered_set<int>*> children;

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }
        auto child = solve(j, node);
        children.push_back(child);
    }
    unordered_set<int>* tmp = new unordered_set<int>();
    tmp->insert(colors[node]);
    children.push_back(tmp);

    unordered_set<int>* res = nullptr;
    for (auto child : children) {
        if (res == nullptr || child->size() > res->size()) {
            res = child;
        }
    }

    for (auto child : children) {
        if (child == res) {
            continue;
        }
        for (auto j : *child) {
            res->insert(j);
        }
        delete child;
    }

    results[node] = res->size();

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> colors[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto res = solve(0, -1);
    delete res;

    for (int i = 0; i < n; i++) {
        cout << results[i] << " \n"[i + 1 == n];
    }
}
