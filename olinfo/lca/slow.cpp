#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, t;
bool visited[MAXN];
int dfs_tree[MAXN];
long long dist[MAXN];
long long branches_sum[MAXN];
int min_found[MAXN];
struct Branch {
    int to;
    int weight;
};
vector<Branch> graph[MAXN];
void dfs (int node) {
    visited[node] = true;
    for (auto branch: graph[node]) {
        if (!visited[branch.to]) {
            dist[branch.to] = dist[node] + 1;
            branches_sum[branch.to] = branches_sum[node] + branch.weight;
            min_found[branch.to] = min(branch.weight, min_found[node]);
            dfs_tree[branch.to] = node;
            dfs(branch.to);
        }
    }
}

void inizia(int N, int T, int A[], int B[], int C[]) {
    n = N;
    t = T;
    for (int i = 0; i < n - 1; i++) {
        graph[A[i]].push_back({ B[i], C[i] });
        graph[B[i]].push_back({ A[i], C[i] });
    }
    return ;
}

long long int distanza1(int u, int v) {
    fill(visited, visited + n, false);
    dist[u] = 0;
    dfs(u);
    return dist[v];
}

long long int distanza2(int u, int v) {
    fill(visited, visited + n, false);
    branches_sum[u] = 0;
    dfs(u);
    return branches_sum[v];
}

long long int minimo(int u, int v) {
    fill(visited, visited + n, false);
    min_found[u] = LLONG_MAX >> 1;
    dfs(u);
    return min_found[v];
}

long long int massimo(int u, int v) {
    distanza2(u, v);

    vector<int> branches;
    for (int node = v; node != u; node = dfs_tree[node]) {
        branches.push_back(branches_sum[node] - branches_sum[dfs_tree[node]]);
    }
    long long best = 0;
    for (int i = 0; i < branches.size(); i++) {
        long long curr = 0;
        for (int j = i; j < branches.size(); j++) {
            curr += branches[j];
            best = max(best, curr);
        }
    }
    return best;
}

