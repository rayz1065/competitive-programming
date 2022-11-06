#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int scores[MAXN];
int max_scores[MAXN];

bool frac_g (int a, int b, int c, int d) {
    // returns whether a/b > c/d
    return (ll) a * d > (ll) c * b;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int tot_score = 0, tot_max_score = 0;
    for (int i = 0; i < n; i++) {
        cin >> scores[i] >> max_scores[i];
        tot_score += scores[i];
        tot_max_score += max_scores[i];
    }
    int best = 0;
    for (int i = 1; i < n; i++) {
        if (frac_g(tot_score - scores[i],    tot_max_score - max_scores[i],
                   tot_score - scores[best], tot_max_score - max_scores[best])) {
            best = i;
        }
    }
    cout << best << "\n";
}
