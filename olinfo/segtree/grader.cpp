#include <iostream>
#include <vector>

using namespace std;

void init(vector<long long> a);
long long get_sum(int l, int r);
void add(int l, int r, long long x);
void set_range(int l, int r, long long x);
long long get_min(int l, int r);
int lower_bound(int l, int r, long long x);

int main() {
#ifndef DEBUG
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    
    int n, q;
    cin >> n >> q;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    init(a);
    
    for (int i = 0; i < q; i++) {
        int op, l, r;
        long long x;
        cin >> op;
        cin >> l >> r;
        if (op == 2 or op == 3 or op == 5)
            cin >> x;
        if (op == 1) cout << get_sum(l, r) << "\n";
        if (op == 2) add(l, r, x);
        if (op == 3) set_range(l, r, x);
        if (op == 4) cout << get_min(l, r) << "\n";
        if (op == 5) cout << lower_bound(l, r, x) << "\n";
    }
    
    return 0;
}
