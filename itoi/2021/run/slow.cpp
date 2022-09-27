#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int distances[MAXN];

int quad_solve () {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int max_found = distances[i];
        for (int j = i; j < n; j++) {
            if (distances[j] < distances[i]) {
                break ;
            }
            if (distances[j] >= max_found) {
                max_found = distances[j];
                s = max(s, j - i + 1);
                // if (s == j - i + 1) {
                    // cout << "From " << i << " to " << j << "\n";
                // }
            }
        }
    }
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> distances[i];
    }

    cout << quad_solve() << "\n";
}