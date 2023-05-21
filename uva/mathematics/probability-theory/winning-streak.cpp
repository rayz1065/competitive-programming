#include <bits/stdc++.h>
#define MAXN 505
#define MAXW 505
using namespace std;

typedef unsigned long long int ll;

double memo[MAXN][MAXW];
double p;

double solve(int gamesLeft, int maxStreak){
    assert(gamesLeft >= 0);
    if(gamesLeft == 0)
        return maxStreak;
    if(memo[gamesLeft][maxStreak] != -1)
        return memo[gamesLeft][maxStreak];

    double S = 0, currProb = 1;
    for(int i = 0; i <= gamesLeft; i++){
        if(i < gamesLeft)
            S+= solve(gamesLeft - i - 1, max(maxStreak, i))*currProb*(1 - p);
        else
            S+= solve(gamesLeft - i, max(maxStreak, i))*currProb;
        currProb*= p;
    }

    return memo[gamesLeft][maxStreak] = S;
}

int main(){
    FILE *out = stdout;

    int N;
    while(cin >> N >> p){
        if(N == 0)
            break ;
        for(int i = 0; i <= N; i++)
            fill(memo[i], memo[i] + N + 1, -1);

        fprintf(out, "%.10f\n", solve(N, 0));
    }
}
