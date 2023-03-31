#include <bits/stdc++.h>
#define MAXN 100005
#define MAXP 1000005

using namespace std;

// era
bool is_prime[MAXP];
int prime_idx[MAXP];
vector<int> primes;

int n;
int values[MAXN];
vector<int> graph[MAXN];
pair<int, int> queries[MAXN];
vector<int> prime_locs[MAXN];
int solutions[MAXN];

bool visited[MAXN];
int anc[20][MAXN];
int depth[MAXN];

int solve (int u, int v) {
    unordered_set<int> found;
    if (depth[u] > depth[v]) swap(u, v);
    while (depth[v] > depth[u]) {
        found.insert(values[v]);
        v = anc[0][v];
    }
    while (u != v) {
        found.insert(values[v]);
        found.insert(values[u]);
        u = anc[0][u], v = anc[0][v];
    }
    found.insert(values[u]);
    for (auto j: primes) {
        if (found.find(j) == found.end()) {
            return j;
        }
    }
    assert(false);
}

void era () {
    // finds all prime numbers up to MAXP
    fill (is_prime, is_prime + MAXP, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAXP; i++) {
        if (!is_prime[i]) continue ;
        prime_idx[i] = primes.size();
        primes.push_back(i);
        for (int j = i * 2; j < MAXP; j += i) {
            is_prime[j] = false;
        }
    }
}

void dfs (int node) { // fills anc[0][*] and depth
    visited[node] = true;
    for (auto j: graph[node]) {
        if (!visited[j]) {
            anc[0][j] = node;
            depth[j] = depth[node] + 1;
            dfs(j);
        }
    }
}

int main () {
    era();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries[i] = { a, b };
        solutions[i] = solve(a, b);
    }
    for (int i = 0; i < q; i++) {
        cout << solutions[i] << "\n";
    }
}
