#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int capacities[MAXN];
int bins[MAXN];

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, k_days;
    cin >> n >> k_days;
    for (int i = 0; i < n; i++) {
        cin >> capacities[i];
    }
    ll s = 0;
    for (int i = 0; i < k_days; i++) {
        int t_type, q_quantity;
        cin >> t_type >> q_quantity;
        if (bins[t_type] + q_quantity > capacities[t_type]) {
            s += capacities[t_type] - bins[t_type];
            bins[t_type] = 0;
        }
        bins[t_type] += q_quantity;
    }
    for (int i = 0; i < n; i++) {
        if (bins[i]) {
            s += capacities[i] - bins[i];
        }
    }
    cout << s << "\n";
}
