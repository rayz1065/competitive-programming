#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN];
vector<int> paths[MAXN];  // id of the path
int node_frequency[MAXN];

bool sort_by_size(set<int> *a, set<int> *b) { return a->size() < b->size(); }

set<int> *solve(int node, int parent) {
    vector<set<int> *> children;

    set<int> *path_ids = new set<int>();

    for (auto j : paths[node]) {
        path_ids->insert(j);
    }

    children.push_back(path_ids);

    for (auto j : graph[node]) {
        if (j != parent) {
            auto child_res = solve(j, node);
            children.push_back(child_res);
        }
    }

    sort(children.begin(), children.end(), sort_by_size);
    path_ids = children.back();
    children.pop_back();

    node_frequency[node] += path_ids->size();

    for (auto j : children) {
        for (auto path_id : *j) {
            if (path_ids->find(path_id) == path_ids->end()) {
                node_frequency[node] += 1;
                path_ids->insert(path_id);
            } else {
                path_ids->erase(path_id);
            }
        }

        delete j;
    }

    return path_ids;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a == b) {
            node_frequency[a] += 1;
        } else {
            paths[a].push_back(q);
            paths[b].push_back(q);
        }
    }

    solve(0, 0);

    for (int i = 0; i < n; i++) {
        cout << node_frequency[i] << " \n"[i + 1 == n];
    }
}
