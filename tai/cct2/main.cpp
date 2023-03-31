#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
#define MAXN 1000005
#define MAXK 55
#define MOD 1000

using namespace std;

int a_pw_memo[MOD], b_pw_memo[MAXK];
int a, b, a_mu, b_mu, a_lambda, b_lambda;
int n, k, curr_pw, curr_mod;
int memo[2][MAXK];

int f(int x){
    return (x * curr_pw) % curr_mod;
}

void turtle_and_hare(int x, int m, int &mu, int &lambda){
    curr_pw = x, curr_mod = m;
    x = 1;
    int t = f(x), h = f(f(x));

    while(t != h)
        t = f(t), h = f(f(h));

    mu = 0;
    h = x;
    while(t != h)
        t = f(t), h = f(h), mu++;

    lambda = 1;
    h = f(h);
    while(t != h)
        h = f(h), lambda++;
}

/*int sqr(int x){
    return x*x;
}

int fast_exp(int x, int pw, int mod){
    if(!pw) return 1;
    if(pw%2) return (sqr(fast_exp(x, pw>>1, mod))*x) % mod;
    return sqr(fast_exp(x, pw>>1, mod)) % mod;
}

int fast_exp_2(int x, int lambda, int mu, int pw, int mod){
    if(pw - mu < 0)
        return fast_exp(x, pw, mod);
    pw = (pw - mu)%lambda + mu;
    return fast_exp(x, pw, mod);
}*/

int fast_exp_3(int x, int lambda, int mu, int pw, int mod, int *memo){
    if(pw < mod)
        return memo[pw];
    pw = (pw - mu)%lambda + mu;
    return memo[pw];
}

int get_cariche(int i){
    return fast_exp_3(b, b_lambda, b_mu, i, k, b_pw_memo);
}

int get_tempo(int i){
    return fast_exp_3(a, a_lambda, a_mu, i, MOD, a_pw_memo);
}

int speedrunna(int n, int k, int a, int b){
    ::a = a, ::b = b, ::n = n, ::k = k;

    turtle_and_hare(a, MOD, a_mu, a_lambda);
    turtle_and_hare(b, k, b_mu, b_lambda);

    a_pw_memo[0] = b_pw_memo[0] = 1;
    for(int i = 1; i < MOD; i++)
        a_pw_memo[i] = (a_pw_memo[i - 1] * a) % MOD;// fast_exp(a, i, MOD);
    for(int i = 1; i <= k; i++)
        b_pw_memo[i] = (b_pw_memo[i - 1] * b) % k; //fast_exp(b, i, k);

    //for(int i = 0; i < 100000; i++)
    //    assert(get_tempo(i) == fast_exp(a, i, MOD) && fast_exp_2(a, a_lambda, a_mu, i, MOD) == fast_exp_3(a, a_lambda, a_mu, i, MOD, a_pw_memo));
    //for(int i = 0; i < 100000; i++)
    //    cout<<i<<"/"<<k<<": "<<get_cariche(i)<<" == "<<fast_exp(b, i, k)<<" && "<<fast_exp_2(b, b_lambda, b_mu, i, k)<<" == "<<fast_exp_3(b, b_lambda, b_mu, i, k, b_pw_memo)<<"\n",
    //    assert(get_cariche(i) == fast_exp(b, i, k) && fast_exp_2(b, b_lambda, b_mu, i, k) == fast_exp_3(b, b_lambda, b_mu, i, k, b_pw_memo));

    for(int i = 0; i <= k; i++)
        memo[n%2][i] = 0;

    bool odd = n%2;
    for(int i = n - 1; i >= 0; i--){
        odd = 1 - odd;
        //cout<<i<<": "<<get_cariche(i)<<", "<<get_tempo(i)<<"\n";
        for(int cariche = 0; cariche <= k; cariche++)
            memo[odd][cariche] = memo[!odd][min(cariche + get_cariche(i), k)] + get_tempo(i);
        memo[odd][k] = min(memo[odd][k], memo[!odd][0]);
    }
    return memo[0][0];
}
