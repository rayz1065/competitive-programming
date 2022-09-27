#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 51
#define MOD 10000019

using namespace std;

unordered_map<int, int> memo[MAXN];
vector<int> visitable;
int dp[2][MOD];
int dist[MOD];
int n, h;

int inverse_mul[] = { 0, 1, 5000010, 3333340, 2500005, 2000004, 1666670, 8571445, 6250012, 4444453 };

void bfs () {
    queue<int> ff;
    fill(dist, dist + MOD, INT_MAX >> 1);
    ff.push(h);
    dist[h] = 0;
    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();
        for (int j = 2; j < 10; j++) {
            int adj = (node * inverse_mul[j]) % MOD;
            if (dist[adj] == INT_MAX >> 1) {
                dist[adj] = dist[node] + 1;
                if (dist[adj] < n) {
                    ff.push(adj);
                }
            }
        }
    }
}

int solve (int i, int curr_h) {
    if (i == n) {
        return curr_h == h;
    }
    if (memo[i].find(curr_h) != memo[i].end()) {
        return memo[i][curr_h];
    }
    int s = 0;
    for (int j = 1; j < 10; j++) {
        s = (s + solve(i + 1, (curr_h * j) % MOD)) % MOD;
    }
    return memo[i][curr_h] = s;
}

void solve_2 () {
    dp[0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (auto j: visitable) {
            dp[(i + 1) % 2][j] = 0;
        }
        for (auto j: visitable) {
            if (dp[i % 2][j] == 0 || dist[j] > n - i) {
                continue ;
            }
            for (int k = 1; k < 10; k++) {
                int reached_h = (j * k) % MOD;
                dp[(i + 1) % 2][reached_h] = (dp[(i + 1) % 2][reached_h] + dp[i % 2][j]) % MOD;
            }
        }
    }
}

int main () {
    cin >> n >> h;
    bfs();
    // int s = 0;
    for (int i = 0; i < MOD; i++) {
        if (dist[i] < n) {
            visitable.push_back(i);
            // s++;
        }
    }
    // cout << s << "\n";

    solve_2();
    cout << dp[n % 2][h] << "\n";
}
