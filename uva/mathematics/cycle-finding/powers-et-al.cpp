#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
string a, b;
int base;

int getLastDigit(string N){
    return N[N.length() - 1] - '0';
}

int f(int x){
    return (x*base)%10;
}

int getCicleLen(int x){
    int t = f(x), h = f(f(x));

    while(t != h)
        t = f(t), h = f(f(h));

    int lambda = 1;
    h = f(x);
    while(h != t)
        h = f(h), lambda++;
    return lambda;
}

int logMod(string N, int mod){
    ll pw = 1, S = 0;

    for(int i = N.length() - 1; i >= 0; i--){
        S = (S + ((ll)(N[i] - '0')*pw)%mod)%mod;
        pw = (pw*10)%mod;
    }

    return S;
}

int powMod10(int base, int exp){
    int S = 1;
    for(int i = 0; i < exp; i++)
        S = (S*base)%10;
    return S;
}

int main(){
    FILE *out = stdout;

    while(cin >> a >> b){
        if(a == "0" && b == "0")
            break ;
        base = getLastDigit(a);
        int lambda = getCicleLen(base);
        int pw = logMod(b, lambda) + lambda;
        if(b == "0")
            pw = 0;

        //printf("base = %d, pw = %d, %d^%d%10 = %d\n", base, pw, base, pw, powMod10(base, pw)%10);
        fprintf(out, "%d\n", powMod10(base, pw)%10);
    }
}
