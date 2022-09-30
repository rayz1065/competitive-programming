#include <bits/stdc++.h>
#define MAXK 205
#define MAXC 10005

using namespace std;
int K, C;
char numeri[MAXK][5];
int costo[MAXK][MAXK];
int memo[MAXK][MAXC];
bool solved[MAXK][MAXC];

int calcolaCosto(char *A, char *B){
    for(int c = 1; c < 4; c++){
        int i = 0;
        while(i + c < 4 && A[i + c] == B[i])
            i++;
        if(i + c == 4)
            return c;
    }
    return 4;
}

int solve(int last, int rem){
    assert(last < K && last >= 0 && rem >= 0);
    if(solved[last][rem])
        return memo[last][rem];
    solved[last][rem] = true;
    int S = 0;
    for(int i = 0; i < K; i++){
        if(rem - costo[last][i] >= 0)
            S = max(S, solve(i, rem - costo[last][i]));
    }
    return memo[last][rem] = S + 1;
}

void findSol(int last, int rem){
    assert(last < K && last >= 0 && rem >= 0 && solved[last][rem]);
    int S = 0;
    for(int i = 0; i < K; i++){
        if(rem - costo[last][i] >= 0){
            if(memo[last][rem] - 1 == memo[i][rem - costo[last][i]]){
                for(int c = 4 - costo[last][i]; c < 4; c++)
                    cout<<numeri[i][c];
                findSol(i, rem - costo[last][i]);
                return ;
            }
        }
    }
    for(int c = 0; c < rem; c++)
        cout<<0;
}

int main(){
    cin >> K >> C;
    for(int i = 0; i < K; i++){
        for(int j = 0; j < 4; j++)
            cin>>numeri[i][j];
    }

    for(int i = 0; i < K; i++){
        for(int j = 0; j < K; j++){
            costo[i][j] = calcolaCosto(numeri[i], numeri[j]);
        }
    }

    int S = 0;
    for(int i = 0; i < K; i++)
        S = max(S, solve(i, C - 4));

    for(int i = 0; i < K; i++){
        if(memo[i][C - 4] == S){
            cout<<numeri[i];
            findSol(i, C - 4);
            cout<<endl;
            return 0;
        }
    }
}
