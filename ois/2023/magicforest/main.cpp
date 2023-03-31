#include <bits/stdc++.h>
#define MAXN 500005
#define MAXM 1000005
#define MOD 1000000007

using namespace std;

typedef long long ll;

struct Branch {
    int a, b, score;
} branches[MAXM];
unordered_map<ll, vector<int>> graph;
unordered_map<ll, int> memo;

inline ll get_key (int node, int score) {
    return (ll) node * MOD + score;
}

int solve (int node, int score) {
    ll memo_key = get_key(node, score);
    if (memo.find(memo_key) != memo.end()) return memo[memo_key];
    int s = 1;
    score += 1;
    for (auto b: graph[get_key(node, score)]) {
        s += solve(b, score);
        s %= MOD;
    }
    memo[memo_key] = s;
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, score;
        cin >> a >> b >> score;
        a--, b--;
        graph[get_key(a, score)].push_back(b);
        graph[get_key(b, score)].push_back(a);
        branches[i] = { a, b, score };
    }
    int s = 0;
    for (int i = 0; i < m; i++) {
        auto b = branches[i];
        s += solve(b.a, b.score);
        s %= MOD;
        s += solve(b.b, b.score);
        s %= MOD;
    }
    cout << (s - m + MOD) % MOD << "\n";
}
