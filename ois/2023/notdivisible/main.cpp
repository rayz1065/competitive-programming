#include <bits/stdc++.h>
#define MAXN 100005
#define MAXP 1000005
#define BUCKET 1024
#define ANCSIZE 17

using namespace std;

// era
bool is_prime[MAXP];
int prime_idx[MAXP];
vector<int> primes;

int n;
int values[MAXN];
vector<int> graph[MAXN];
pair<int, int> queries[MAXN];
int solutions[MAXN];

bool visited[MAXN];
int depth[MAXN];
int anc[ANCSIZE][MAXN];
bitset<BUCKET> anc_primes[ANCSIZE][MAXN];

// int solve (int u, int v) {
//     unordered_set<int> found;
//     if (depth[u] > depth[v]) swap(u, v);
//     while (depth[v] > depth[u]) {
//         found.insert(values[v]);
//         v = anc[0][v];
//     }
//     while (u != v) {
//         found.insert(values[v]);
//         found.insert(values[u]);
//         u = anc[0][u], v = anc[0][v];
//     }
//     found.insert(values[u]);
//     for (auto j: primes) {
//         if (found.find(j) == found.end()) {
//             return j;
//         }
//     }
//     assert(false);
// }

void calc_anc_primes (int first_prime_idx) {
    // constructs anc_primes with next BUCKET primes
    int last_prime_idx = first_prime_idx + BUCKET;
    for (int i = 0; i < n; i++) {
        if (first_prime_idx <= prime_idx[values[i]] && prime_idx[values[i]] < last_prime_idx) {
            anc_primes[0][i].set(prime_idx[values[i]] - first_prime_idx);
        } else {
            anc_primes[0][i] = 0;
        }
    }
    for (int k = 1; k < ANCSIZE; k++) {
        for (int i = 0; i < n; i++) {
            if (anc[k][i] == -1) continue ;
            int tmp = anc[k - 1][i];
            anc_primes[k][i] = anc_primes[k - 1][i] | anc_primes[k - 1][tmp];
        }
    }
}

void build_anc () {
    for (int k = 1; k < ANCSIZE; k++) {
        for (int i = 0; i < n; i++) {
            anc[k][i] = -1;
            int tmp = anc[k - 1][i];
            if (tmp == -1) continue ;
            anc[k][i] = anc[k - 1][tmp];
        }
    }
}

int solve_2 (int u, int v) {
    // returns the delta index of a prime if it's the solution, -1 otherwise
    bitset<BUCKET> found(0);
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = ANCSIZE - 1; k >= 0; k--) { // reach same depth
        if ((depth[v] - depth[u]) & (1 << k)) {
            found |= anc_primes[k][v];
            v = anc[k][v];
        }
    }
    for (int k = ANCSIZE - 1; k >= 0; k--) {
        if (anc[k][u] != anc[k][v]) {
            found |= anc_primes[k][v] | anc_primes[k][u];
            v = anc[k][v], u = anc[k][u];
        }
    }
    found |= anc_primes[0][u] | anc_primes[0][v];
    if (u != v) {
        found |= anc_primes[0][anc[0][v]];
    }
    int res = (~found)._Find_first();
    return res == BUCKET ? -1 : res;
}

void era () {
    // finds all prime numbers up to MAXP
    fill(is_prime, is_prime + MAXP, true);
    fill(prime_idx, prime_idx + MAXP, -1);
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
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int q;
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

    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries[i] = { a, b };
    }

    era();
    anc[0][0] = -1;
    dfs(0);
    build_anc();
    fill(solutions, solutions + q, -1);
    int missing = q;
    for (int first_prime_idx = 0; missing; first_prime_idx += BUCKET) {
        calc_anc_primes(first_prime_idx);
        for (int i = 0; i < q; i++) {
            if (solutions[i] != -1) continue ;
            int res = solve_2(queries[i].first, queries[i].second);
            if (res == -1) continue ;
            solutions[i] = primes[first_prime_idx + res];
            // cerr << "solution: " << solve(queries[i].first, queries[i].second) << ", found: " << solutions[i] << "\n";
            // assert(solutions[i] == solve(queries[i].first, queries[i].second));
            missing -= 1;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << solutions[i] << "\n";
    }
}
