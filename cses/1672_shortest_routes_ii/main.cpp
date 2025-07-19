#include <bits/stdc++.h>
#define MAXN 505
#define INF (LLONG_MAX >> 1)

using namespace std;

typedef long long ll;

int n;
ll distances[MAXN][MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < n; i++) {
        fill(distances[i], distances[i] + n, INF);
        distances[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        distances[u][v] = distances[v][u] = min(distances[u][v], (ll)w);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                distances[i][j] =
                    min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        ll res = distances[u][v];
        cout << (res == INF ? -1 : res) << "\n";
    }
}
