#include <bits/stdc++.h>
#define MAXN 50005
#define MAXM 21
#define LOG2MAXN 20 // 15,6...
#define MOD 1000000007
using namespace std;

class gcdt{
    private:int N;
    private:int gcdTable[MAXN][LOG2MAXN];

    private:int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public:int rangeGcd(int a, int len){
        int l = log2(len);
        if((1<<l) == len)
            return gcdTable[a][l];
        return gcd(gcdTable[a][l], rangeGcd(a + (1<<l), len - (1 << l)));
    };

    public:void initialize(int N, int casa[]){
        this->N = N;
        for(int i = 0; i < N; i++)
            gcdTable[i][0] = casa[i];
        for(int l = 1; l < LOG2MAXN; l++){
            for(int i = 0; i < N && (1 << l) + i <= N; i++){
                gcdTable[i][l] = gcd(gcdTable[i][l - 1], gcdTable[i + (1 << (l - 1))][l - 1]);
            }
        }
    };

    public:void stampa(){
        cout<<"\n---------------------\n\nQuesto e' il contenuto della tabella gcdTable\n\n";
        for(int l = 1; l < LOG2MAXN && (1 << l) <= N; l++){
            for(int i = 0; i < N && (1 << l) + i <= N; i++){
                cout<<gcdTable[i][l]<<"\t";
            }
            cout<<endl;
        }
        cout<<"\n---------------------\n\n";
    }
} gcdTable;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool solved[MAXN][MAXM];
long long memo[MAXN][MAXM];
long long casi[MAXN][MAXM];
int N;
int casa[MAXN];

long long dp(int a, int k){
    if(!solved[a][k]){
        solved[a][k] = true;
        long long S = 0, V = 0;
        assert(k > 0);
        if(k == 1){
            int currGcd = casa[a];
            for(int len = 1; len + a <= N; len++){
                currGcd = gcd(currGcd, casa[a + len - 1]);
                S+= currGcd;
                V++;
            }
        }
        else{
            int currGcd = casa[a];
            for(int len = 1; len + a <= N - k + 1; len++){
                currGcd = gcd(currGcd, casa[a + len - 1]);
                if(dp(a + len, k - 1) > 0){
                    //cout<<"dp["<<a<<"]["<<k<<"]+= "<<"dp["<<a + len<<"]["<<k - 1<<"]\n";
                    S+= memo[a + len][k - 1] + currGcd * casi[a + len][k - 1];
                    V+= casi[a + len][k - 1];
                }
            }
        }
        if(a + 1 < N){
            S+= dp(a + 1, k);
            V+= casi[a + 1][k];
            //cout<<"dp["<<a<<"]["<<k<<"]+= dp["<<a + 1<<"]["<<k<<"]\n";
        }
        memo[a][k] = S % MOD;
        casi[a][k] = V % MOD;
        //cout<<"dp ["<<a<<"]["<<k<<"] = "<<memo[a][k]<<endl;
    }
    return memo[a][k];
}

int main(){
    int K;
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>K;

    for(int i = 0; i < N; i++)
        cin>>casa[i];
    //cout<<"\n------------------\n\n";
    /*for(int i = 0; i < N; i++)
        cout<<casa[i]<<"\t";
    cout<<endl;*/

    //gcdTable.initialize(N, casa);
    /*for(int i = 0; i < N; i++){
        for(int len = 1; i + len <= N; len++)
            cout<<gcdTable.rangeGcd(i, len)<<"\t";
        cout<<endl;
    }*/

    cout<<dp(0, K)<<endl;
}
