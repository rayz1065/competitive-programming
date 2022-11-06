#include <bits/stdc++.h>
#define MAXN 10005
#define MAXC 105

using namespace std;

struct Branch {
    int to;
    int coins;
};

int n, m, c0;
int mx_diff[MAXN][MAXC];
int diff[MAXN];
vector<Branch> graph[MAXN];

int solve () {
    for (int i = 0; i < n; i++) {
        fill(mx_diff[i], mx_diff[i] + MAXC, INT_MAX >> 1);
    }
    set<pair<int, pair<int, int>>> ff;
    ff.insert({ mx_diff[0][c0] = 0, { 0, c0 }});
    int s = INT_MAX >> 1;
    while (!ff.empty()) {
        auto curr = ff.begin();
        int node = curr->second.first, coins = curr->second.second;
        if (node == n - 1) {
            break ;
        }
        ff.erase(curr);
        if (curr->first > mx_diff[node][coins]) {
            continue ; // worst than current
        }
        for (auto b: graph[node]) {
            for (int used = 0; used <= coins; used++) {
                int new_coins = coins - used + b.coins;
                int new_diff = max(mx_diff[node][coins], diff[node] >> used);
                if (new_diff < mx_diff[b.to][new_coins] && new_diff < s) {
                    ff.erase({ mx_diff[b.to][new_coins], { b.to, new_coins }});
                    ff.insert({ new_diff, { b.to, new_coins }});
                    mx_diff[b.to][new_coins] = new_diff;
                    if (b.to == n - 1) {
                        s = min(s, new_diff);
                    }
                }
                if ((diff[node] >> used) < mx_diff[node][coins]) {
                    break ; // no need to use more coins
                }
            }
        }
    }
    return s;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> c0;
    for (int i = 0; i < n; i++) {
        cin >> diff[i];
    }
    // dummy node
    diff[n] = 0, graph[n - 1].push_back({ n, 0 }); n++;
    for (int i = 0; i < m; i++) {
        int a, b, coins;
        cin >> a >> b >> coins;
        graph[a].push_back({ b, coins });
    }
    cout << solve() << "\n";
}
