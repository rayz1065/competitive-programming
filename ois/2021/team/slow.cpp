#include <bits/stdc++.h>
#define MAXN 505

using namespace std;

int best;
int n, adj_mat[MAXN][MAXN], meeting[MAXN];
int visited[MAXN];

void solve (int curr, int repr) {
    // curr representative is in curr, where next?
    bool found = false, unvisited = false;
    for (int i = 0; i < n; i++) {
        unvisited |= !visited[i];
        if (!visited[i] && adj_mat[curr][i] + meeting[curr] <= meeting[i]) {
            visited[i] = repr;
            solve(i, repr);
            visited[i] = 0;
            found = true;
        }
    }
    if (!unvisited) {
        // visited all
        if (repr < best) {
            best = repr;
            for (int i = 0; i < n; i++) {
                // cout << visited[i] << " \n"[i + 1 == n];
            }
        }
        return ;
    }
    if (!found) {
        // new representative
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = repr + 1;
                solve(i, repr + 1);
                visited[i] = 0;
            }
        }
    }
}

int main () {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> meeting[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj_mat[i][j];
        }
    }
    
    best = INT_MAX >> 1;
    for (int i = 0; i < n; i++) {
        visited[i] = 1;
        solve(i, 1);
        visited[i] = 0;
    }
    cout << best << "\n";
}