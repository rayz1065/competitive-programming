#include <bits/stdc++.h>
#define MAXN 55

using namespace std;
int N, K;
long long libri[MAXN], maxS = 0;

void solve(int k, int i, long long S){
    //cout<<k<<" "<<i<<" "<<S<<endl;
    long long p = 0;
    if(k == K - 1){
        for(; i < N; i++)
            p+= libri[i];
        maxS = max((S & p), maxS);
        return;
    }

    while(N - i >= K - k){
        p+= libri[i];
        if((S & p) > maxS){
            solve(k + 1, i + 1, S & p);
        }
        i++;
    }
}

int main(){
    cin >> N >> K;
    for(int i = 0; i < N; i++)
        cin >> libri[i];
    long long S = ((long long)1 << 63) - 1;
    solve(0, 0, S);
    cout<<maxS;
}
