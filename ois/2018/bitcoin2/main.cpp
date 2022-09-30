#include <bits/stdc++.h>
#define MAXN 305
#define posMin 303
#define posMax 304
#define VMAX 1000000005
using namespace std;

int N;
int memo[MAXN][MAXN][MAXN][2]; // minimo, massimo, auttuale, isMax
int prezzi[MAXN];

int solve(int minV, int maxV, int i, bool isMax){
    if(i == N){
        return 0;
    }
    if(memo[minV][maxV][i][isMax] == 0){
        if(prezzi[i] >= prezzi[maxV] || prezzi[i] <= prezzi[minV])
            memo[minV][maxV][i][isMax] = solve(minV, maxV, i + 1, isMax) + 1;
        else{
            if(isMax){
                memo[minV][maxV][i][isMax] = solve(minV, i, i + 1, 1 - isMax);
                if(memo[minV][maxV][i][isMax] != 0)
                    memo[minV][maxV][i][isMax] = min(solve(minV, maxV, i + 1, isMax) + 1, memo[minV][maxV][i][isMax]);
            }
            else{
                memo[minV][maxV][i][isMax] = solve(i, maxV, i + 1, 1 - isMax);
                if(memo[minV][maxV][i][isMax] != 0)
                    memo[minV][maxV][i][isMax] = min(solve(minV, maxV, i + 1, isMax) + 1, memo[minV][maxV][i][isMax]);
            }
        }
        memo[minV][maxV][i][isMax]++;
    }
    return memo[minV][maxV][i][isMax] - 1;
}

int main(){
    cin>>N;
    for(int i = 0; i < N; i++)
        cin>>prezzi[i];

    prezzi[posMin] = 0;
    prezzi[posMax] = VMAX;
    cout<<min(solve(posMin, posMax, 0, 0), solve(posMin, posMax, 0, 1));
}
