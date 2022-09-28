#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 100005
#define MAXS 2000005
#define MOD 1000000007

using namespace std;

int n, k;
int buildings[MAXN];
int fenwick[MAXN];
unsigned long long fac[MAXN + MAXS];

void fenwick_set(int i, int v) {
    i++;
    while (i < MAXN) {
        fenwick[i] += v;
        i += i & (-i);
    }
}

int fenwick_sum(int i) {
    int sum = 0;
    i++;
    while (i > 0) {
        sum+= fenwick[i];
        i -= i & (-i);
    }
    return sum;
}

int range_sum (int a, int b) {
    if (a == 0) {
        return fenwick_sum(b);
    }
    return fenwick_sum(b) - fenwick_sum(a - 1);
}

void set_building_value (int building, int value) {
    int old_value = buildings[building];
    value = max(value, k);
    // cout << "updating " << building << " from " << old_value << " to " << value << "\n";
    buildings[building] = value;
    fenwick_set(building, value - old_value);
}

unsigned long long power(unsigned long long x,
                                  int y, int p)
{
    unsigned long long res = 1; // Initialize result
 
    x = x % p; // Update x if it is more than or
    // equal to p
 
    while (y > 0)
    {
     
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;
 
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
 
// Returns n^(-1) mod p
unsigned long long modInverse(unsigned long long n, 
                                            int p)
{
    return power(n, p - 2, p);
}
 
// Returns nCr % p using Fermat's little
// theorem.
unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p)
{
    // If n<r, then nCr should return 0
    if (n < r)
        return 0;
    // Base case
    if (r == 0)
        return 1;
 
    return (fac[n] * modInverse(fac[r], p) % p
            * modInverse(fac[n - r], p) % p)
           % p;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q >> k;

    fac[0] = 1;
    for (int i = 1; i < MAXN + MAXS; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        set_building_value(i, v);
    }

    while (q--) {
        int action;
        cin >> action;

        if (action == 1) {
            // building changed it's value
            int building, value;
            cin >> building >> value;
            building--;
            set_building_value(building, value);
        } else {
            // calculate combinations
            int l, r, sum;
            cin >> l >> r >> sum;
            l--; r--;
            int true_sum = range_sum(l, r);
            // cout << "from " << l << " to " << r << " sum is " << range_sum(l, r) << " instead of " << sum << "\n";
            // for (int i = l; i <= r; i++) {
            //     cout << buildings[i] << " ";
            // }
            // cout << "\n";
            int balls = sum - range_sum(l, r);
            int sticks = r - l;
            if (true_sum > sum) {
                cout << 0 << "\n";
            } else {
                cout << nCrModPFermat(balls + sticks, sticks, MOD) << "\n";
            }
        }
    }
}