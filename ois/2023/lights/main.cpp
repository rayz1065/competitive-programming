#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int lights[MAXN];
int freqs[MAXN];

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, c;
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        cin >> lights[i];
    }
    int i = 0, j = 0, found_colors = 0;
    while (found_colors < c) {
        found_colors += freqs[lights[j]] == 0;
        freqs[lights[j++]] += 1;
    }
    int best = j - i;
    while (true) {
        if (freqs[lights[i]] > 1) {
            freqs[lights[i++]] -= 1;
            best = min(best, j - i);
        } else if (j < n) {
            freqs[lights[j++]] += 1;
        } else {
            break ;
        }
    }
    cout << best << "\n";
}
