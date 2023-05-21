#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int N, mod;

ll pow(int b, int p){
    int S = 1;
    for(int i = 0; i < p; i++)
        S*= b;
    return S;
}

int f(int x){
    ll S = ((ll)x*x);
    while(S >= mod)
        S/= 10;
    return S;
}

int solve(int x){
    int t = f(x), h = f(f(x));
    while(t != h)
        t = f(t), h = f(f(h));

    int mu = 0; h = x;
    while(t != h)
        t = f(t), h = f(h), mu++;
    int lambda = 1; h = f(t);
    while(t != h)
        h = f(h), lambda++;

    int best = -1; h = x;
    for(int i = 0; i < mu + lambda; i++)
        best = max(best, h), h = f(h);
    return best;
}

int main(){
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        int x;
        cin >> N >> x;
        mod = pow(10, N);
        printf("%d\n", solve(x));
    }
}
