#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sqr (int x) {
    return (ll) x * x;
}

double tc () {
    int xa, ya, xb, yb, xc, yc, r;
    cin >> xa >> ya >> xb >> yb >> xc >> yc >> r;

    double dist = sqrt(sqr(xa - xb) + sqr(ya - yb));
    double dist_a_c = max(0., sqrt(sqr(xa - xc) + sqr(ya - yc)) - r);
    double dist_b_c = max(0., sqrt(sqr(xb - xc) + sqr(yb - yc)) - r);
    // cout << dist << ", " << dist_a_c << " + " << dist_b_c << "\n";

    return min(dist, dist_a_c + dist_b_c);
}

int main () {
    int t;
    cin >> t;
    while (t--) printf("%.6f\n", floor(tc() * 1e6)/1e6);
}
