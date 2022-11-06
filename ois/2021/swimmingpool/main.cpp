#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int positions[MAXN];

int main () {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> positions[i];
    }
    int best_dist = INT_MAX >> 1;
    for (int i = 0; i < n; i++) {
        int new_dist = max(positions[i] - positions[0],
            positions[n - 1] - positions[i]);
        if (new_dist < best_dist) {
            best_dist = new_dist;
        }
    }
    cout << best_dist << "\n";
}
