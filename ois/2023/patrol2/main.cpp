#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, l_loop;
vector<int> graph[MAXN];
int guarded[MAXN];
int dist[MAXN];

int solve () {
    vector<queue<int>> ffs(3);
    int curr_dist = 0;
    fill(dist, dist + n, INT_MAX >> 1);
    dist[0] = 0;
    ffs[curr_dist % 3].push(0);
    while (!ffs[curr_dist % 3].empty()) {
        int node = ffs[curr_dist % 3].front();
        ffs[curr_dist % 3].pop();
        for (auto j: graph[node]) {
            int new_dist = dist[node] + 1;
            new_dist += guarded[new_dist % l_loop] == j; // if guarded, wait
            if (new_dist < dist[j]) {
                dist[j] = new_dist;
                ffs[new_dist % 3].push(j);
            }
        }
        for (int k = 0; k < 3 && ffs[curr_dist % 3].empty(); k++, curr_dist++);
    }
    return dist[n - 1];
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m_edges;
    cin >> n >> m_edges >> l_loop;
    while (m_edges--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < l_loop; i++) {
        cin >> guarded[i];
    }

    cout << solve() << "\n";
}
