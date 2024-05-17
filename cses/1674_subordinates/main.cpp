#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];
int subtree_size[MAXN];

int get_subtree_size(int node, int parent) {
    subtree_size[node] = 1;
    for (auto j : graph[node]) {
        if (j != parent) {
            subtree_size[node] += get_subtree_size(j, node);
        }
    }

    return subtree_size[node];
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--;
        graph[parent].push_back(i);
    }

    get_subtree_size(0, 0);

    for (int i = 0; i < n; i++) {
        cout << subtree_size[i] - 1 << " \n"[i + 1 == n];
    }
}
