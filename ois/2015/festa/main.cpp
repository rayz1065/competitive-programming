#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n;
vector<int> graph[MAXN];
int degree[MAXN];
bool present[MAXN];

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u] += 1;
        degree[v] += 1;
    }

    fill(present, present + n, true);

    queue<int> ff;
    for (int i = 0; i < n; i++) {
        if (degree[i] < 2) {
            present[i] = false;
            ff.push(i);
        }
    }

    int res = n;
    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();
        res -= 1;
        for (auto j : graph[node]) {
            if (!present[j]) continue;
            degree[j] -= 1;
            if (degree[j] < 2) {
                present[j] = false;
                ff.push(j);
            }
        }
    }

    cout << res << "\n";
}
