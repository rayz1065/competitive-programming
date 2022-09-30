#include <bits/stdc++.h>
#define MAXK 205
#define MAXC 10005

using namespace std;
int K, C;
bool isNum[10000];
int numeri[MAXK];
int memo[1000][MAXC];
bool solved[1000][MAXC];

int solve(int lastThree, int rem){
    if(solved[lastThree][rem])
        return memo[lastThree][rem];
    solved[lastThree][rem] = true;
    if(rem == 0)
        return 0;
    int remFirst = (lastThree - (lastThree/100)*100)*10;
    int maxS = 0;
    for(int i = 0; i < 10; i++){
        maxS = max(maxS, solve(remFirst + i, rem - 1) + isNum[lastThree*10 + i]);
    }
    return memo[lastThree][rem] = maxS;
}

void findSol(int lastThree, int rem){
    if(rem == 0)
        return ;
    int remFirst = (lastThree - (lastThree/100)*100)*10;
    for(int i = 0; i < 10; i++){
        if(memo[remFirst + i][rem - 1] + isNum[lastThree*10 + i] == memo[lastThree][rem]){
            cout<<i;
            findSol(remFirst + i, rem - 1);
            return ;
        }
    }
    assert(false);
}

int main(){
    cin >> K >> C;
    for(int i = 0; i < K; i++){
        cin>>numeri[i];
        isNum[numeri[i]] = true;
    }

    int S = 0;
    for(int i = 0; i < K; i++){
        S = max(S, solve(numeri[i] - (numeri[i]/1000)*1000, C - 4) + 1);
    }

    for(int i = 0; i < K; i++){
        if(S == memo[numeri[i] - (numeri[i]/1000)*1000][C - 4] + 1){
           cout<<numeri[i];
           findSol(numeri[i] - (numeri[i]/1000)*1000, C - 4);
           return 0;
        }
    }
}
