#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int muffin[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    int S = 0;
    cin>>N>>M;

    for(int i = 0; i < M; i++){
        cin>>muffin[i];
        S+= muffin[i];
    }

    int bestS = S;

    for(int i = M; i < N; i++){
        cin>>muffin[i];
        S+= muffin[i] - muffin[i - M];
        bestS = max(bestS, S);
    }

    cout<<bestS;
}
