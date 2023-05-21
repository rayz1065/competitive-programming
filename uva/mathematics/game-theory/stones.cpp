#include <bits/stdc++.h>
#define memoria 1001
using namespace std;

int memo[memoria][memoria];


bool canWin(int N, int ruba){
    if(ruba>=N)
        return true;
    if(memo[N][ruba]==0){
        for(int i=1; i<=ruba&&i<=N/3; i++)
            if(!canWin(N-i, i*2))
                memo[N][ruba]=2;
        if(memo[N][ruba]==0)
            memo[N][ruba]=1;
    }
    return memo[N][ruba]-1;
}

int main(){
    int N;
    cin>>N;
    while(N!=0){
        cout<<(canWin(N, N-1)?"Alicia":"Roberto")<<endl;
        cin>>N;
    }
}
