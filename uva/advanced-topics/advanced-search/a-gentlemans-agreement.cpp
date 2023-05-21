#include <bits/stdc++.h>
#define MAXN 100

using namespace std;

int nSets;
int biggestSet;

int n, r;

bool adjMat[MAXN][MAXN];
bool taken[MAXN];

void init(){
    memset(adjMat, 0, sizeof adjMat);

    cin >> n >> r;
    for(int i = 0; i < r; i++){
        int a, b;
        cin >> a >> b;
        adjMat[a][b] = adjMat[b][a] = true;
    }
    nSets = biggestSet = 0;
}

bool isAnyTaken(int i){
    for(int j = 0; j < n; j++)
        if(adjMat[i][j] && taken[j])
            return true;
    return false;
}

int getHeighest(int i){
    for(int j = n - 1; j >= 0; j--)
        if(adjMat[i][j])
            return j;
}

void solve(int i){
    if(i == n){
        int s = 0;
        for(i = 0; i < n; i++){
            if(!taken[i] && !isAnyTaken(i))
                return ;
            s+= taken[i];
        }
        biggestSet = max(biggestSet, s);
        nSets++;
        return ;
    }

    if(!isAnyTaken(i)){
        taken[i] = true;
        solve(i + 1);
        taken[i] = false;

        if(getHeighest(i) > i)
            solve(i + 1);
    }
    else{
        solve(i + 1);
    }
}

void solve(){
    solve(0);
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();

        cout<<nSets<<"\n"<<biggestSet<<"\n";
    }
}
