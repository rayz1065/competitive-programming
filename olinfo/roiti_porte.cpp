#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 400005
using namespace std;

typedef int lli;

int N;
lli numeri[MAXN];
lli dp[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>N;
    for(int i = 0; i < N; i++)
        in>>numeri[i];

    dp[N - 1] = 1;
    for(int i = N - 2; i >= 0; i--){
        for(int j = 1; i + j < N; j<<= 1){
            if((numeri[i] + numeri[i + j]) % j == 0){
                dp[i] = (dp[i] + dp[i + j])%MOD;
            }
        }
    }
    out<<dp[0]<<endl;
}
