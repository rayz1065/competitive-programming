#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n, k;
vector<int> graph[MAXN];
int k_ancestor[MAXN];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

void dfs(int node, int parent, vector<int> &ancestors) {
    // check for ancestor
    if (ancestors.size() >= k) {
        k_ancestor[node] = ancestors[ancestors.size() - k];
    } else {
        k_ancestor[node] = -1;
    }

    ancestors.push_back(node);

    for (auto j: graph[node]) {
        if (j == parent) {
            continue ;
        }

        dfs(j, node, ancestors);
    }

    ancestors.pop_back();
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin(), k = fastin();
    for (int i = 0; i < n - 1; i++) {
        int a = fastin(), b = fastin();
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> ancestors;
    dfs(0, -1, ancestors);

    for (int i = 0; i < n; i++) {
        cout << k_ancestor[i] << " \n"[i + 1 == n];
    }
}
