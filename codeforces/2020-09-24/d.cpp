#include <bits/stdc++.h>
#define MAXN 300015
#define MOD 998244353

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pii;

int n, k;
lli a[MAXN];
int l[MAXN], r[MAXN];
lli fact_memo[MAXN];

void init(){
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> l[i] >> r[i];
    l[n] = r[n] = INT_MAX >> 1;
}

lli gcdExtended(lli a, lli b, lli *x, lli *y);

// Function to find modulo inverse of a
lli modInverse(lli a, lli m)
{
    lli x, y;
    lli g = gcdExtended(a, m, &x, &y);
    // m is added to handle negative x
    lli res = (x%m + m) % m;
    return res;
}

// C function for extended Euclidean Algorithm
lli gcdExtended(lli a, lli b, lli *x, lli *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    lli x1, y1; // To store results of recursive call
    lli gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

lli fact(int n){
    return fact_memo[n];
}

lli chooseb(int n, int k){
    return fact(n)/(fact(n - k)*fact(k));
}

lli choose(int n, int k){
    if(n == k || k == 0) return 1;
    return (fact(n)*modInverse(fact(n - k)*fact(k), MOD))%MOD;
}

lli solve(){
    sort(l, l + n);
    sort(r, r + n);

    int lidx = 0, ridx = 0;
    int amOn = 0;
    lli tot = 0;

    while(lidx < n || ridx < n){
        //cout<<l[lidx]<<"\t"<<r[ridx]<<"\t"<<amOn<<" => ";

        if(lidx < n && ridx < n){
            if(l[lidx] <= r[ridx]){
                lidx++, amOn++;
                if(amOn >= k){
                    tot = (tot + choose(amOn - 1, k - 1))%MOD;
                }
            }
            else
                ridx++, amOn--;
        }
        else if(ridx < n)
            ridx++, amOn--;
        else if(lidx < n)
            assert(false); // can't happen

        //cout<<amOn<<"\t"<<tot<<"\n";
    }

    return tot%MOD;
}

int main(){
    fact_memo[0] = 1;
    for(int i = 1; i < MAXN; i++)
        fact_memo[i] = (fact_memo[i - 1] * i)%MOD;

    init();
    cout<<solve()<<"\n";
}
