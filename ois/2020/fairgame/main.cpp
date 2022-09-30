#include <bits/stdc++.h>
#define MAXN 10005 // 5000005

using namespace std;

int n, k;
int m, p, q; // m: pay to take odd,
             // p: get by ending game,
             // q: get by not ending game


int memo[MAXN];

void init(){
    cin >> n >> k >> m >> p >> q;
    fill(memo, memo + n + 1, INT_MIN/2);
}

int solve(int x){
    if(memo[x] != INT_MIN/2)
        return memo[x];

    if(x == 0)
        return memo[x] = q - p;

    int s = INT_MIN/2;

    for(int i = 1; i <= k && x - i >= 0; i++){
        if(i%2) // odd
            s = max(s, -m - solve(x - i));
        else
            s = max(s, -solve(x - i));
    }

    return memo[x] = s;
}

int print(int x){
    if(x == 0){
        cout<<"0: end, "<<solve(0)<<"\n";
        return 0;
    }

    int s = solve(x), sol = 0;

    for(int i = min(k, x); i >= 1; i--){
        if(i%2){ // odd
            if(-m - solve(x - i) == s){
                cout<<x<<"\ttake "<<i<<"\tleave "<<x - i<<"\t"<<s<<"\n";
                return i;
            }
        }
        else{
            if(-solve(x - i) == s){
                cout<<x<<"\ttake "<<i<<"\tleave "<<x - i<<"\t"<<s<<"\n";
                return i;
            }
        }
    }

    cout<<x<<": dunno\n";
    assert(false);
}

int main(){
    init();
    cout<<solve(n)<<"\n\n";
    for(int i = 0; i <= n; i++)
        print(i);
    cout<<"\n";
}
