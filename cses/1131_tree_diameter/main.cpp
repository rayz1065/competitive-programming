#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];
int distances[MAXN];

void dfs(int node, int parent) {
    for (auto j : graph[node]) {
        if (j != parent) {
            distances[j] = distances[node] + 1;
            dfs(j, node);
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0, 0);

    int farthest = max_element(distances, distances + n) - distances;
    distances[farthest] = 0;
    dfs(farthest, farthest);

    cout << *max_element(distances, distances + n) << "\n";
}
