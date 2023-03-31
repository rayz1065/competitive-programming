#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
int N;

int memo[MAXN][2];

int dp(int giorno, bool canTakeTrainB, int a[], int b[]){
    if(giorno == N)
        return 0;
    if(memo[giorno][canTakeTrainB] == 0){
        int bestVal = dp(giorno + 1, 1, a, b); // non prendiamo il treno

        if(canTakeTrainB)
            bestVal = max(bestVal, dp(giorno + 1, 0, a, b) + b[giorno]);
        bestVal = max(bestVal, dp(giorno + 1, 0, a, b) + a[giorno]);
        memo[giorno][canTakeTrainB] = bestVal + 1;
    }
    return memo[giorno][canTakeTrainB] - 1;
}

int tempo_massimo(int n, int a[], int b[]){
    N = n;
    return dp(0, 1, a, b);
}
