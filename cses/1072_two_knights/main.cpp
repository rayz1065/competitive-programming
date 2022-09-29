#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n;
long long sols[MAXN] = { 0, 0, 6, 28 };

int main () {
    cin >> n;
    for (int k = 4; k <= n; k++) {
        long long edge_size = 2 * k - 1;
        long long n_corners = 3, n_close_corners = 4;
        long long n_middle = edge_size - n_corners - n_close_corners;
        // max amount of combinations
        long long tot = edge_size * (k - 1) * (k - 1) + (edge_size * (edge_size - 1)) / 2;
        // corner to center attacks
        tot -= 2 * n_corners;
        // close to corner
        tot -= 3 * n_close_corners;
        // middle
        tot -= 4 * n_middle;
        sols[k] = sols[k - 1] + tot + 2;
        
    }
    for (int k = 1; k <= n; k++) {
        cout << sols[k] << "\n";
    }
}