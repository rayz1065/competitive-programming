#include <bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
using namespace std;

int lastSeen[MAXN]; // lastSeen sarà 0 se non è mai stato visto o l'indice + 1 se è stato visto
long long dp[MAXN];
int pow2[MAXN];

int taglia(int N, int V[]){
    for(int i = 0; i < MAXN; i++){
        lastSeen[i] = -1;
    }
    pow2[0] = 1;
    for(int i = 1; i < MAXN; i++)
        pow2[i] = (pow2[i - 1]*2)%MOD;
    int lastSepa = -1;
    dp[0] = 1;
    lastSeen[V[0]] = 0;
    //cout<<0<<" "<<V[0]<<" -> "<<dp[0]<<" "<<lastSepa<<endl;
    for(int i = 1; i < N; i++){
        //cout<<i<<" "<<V[i]<<" "<<lastSeen[V[i]]<<" -> ";
        if(lastSeen[V[i]] < i - 1){
            dp[i] = dp[i - 1]*2;
            if(lastSeen[V[i]] > lastSepa){
                if(lastSepa < 0){
                    //cout<<"(- 2^"<<lastSeen[V[i]]<<") ";
                    dp[i]-= pow2[lastSeen[V[i]]]; // fare con un array
                }
                else{
                    //cout<<"(-2^"<<lastSeen[V[i]] - lastSepa - 1<<"*"<<dp[lastSepa]<<") ";
                    dp[i]-= pow2[lastSeen[V[i]] - lastSepa - 1]*dp[lastSepa]; // fare con un array
                }
                lastSepa = lastSeen[V[i]];
                //cout<<"New last sepa! ";
            }
            dp[i] = dp[i] % MOD;
        }
        else
            dp[i] = dp[i - 1];
        //cout<<dp[i]<<" "<<lastSepa<<endl;
        lastSeen[V[i]] = i;
    }
    return dp[N - 1] % MOD;
}
