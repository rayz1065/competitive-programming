#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

double prob_dies[MAXN];
int tossed[MAXN];

void tc() {
    int n, k;
    cin >> n >> k;

    set<pair<double, int>> bugs;
    for (int i = 0; i < n; i++) {
        tossed[i] = 0;
        cin >> prob_dies[i];
        bugs.insert({-prob_dies[i], i});
    }

    double ev = 0;
    while (k--) {
        auto bug = bugs.begin();
        bugs.erase(bug);
        int i = bug->second;
        ev -= bug->first;
        tossed[i] += 1;
        bugs.insert({-pow(1 - prob_dies[i], tossed[i]) * prob_dies[i], i});
    }

    ev = floor(ev * 1000000) / 1000000;
    cout << fixed << setprecision(6) << ev << "\n";
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) tc();
}
