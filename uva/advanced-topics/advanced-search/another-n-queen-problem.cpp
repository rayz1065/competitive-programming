#include <bits/stdc++.h>
#define MAXN 20
#define MOVEMENTS 3

#pragma GCC optimize ("O3")
using namespace std;

int n;
int nSol;
char gridStr[MAXN][MAXN];
bool canUse[MAXN][MAXN];

bool diagUsed[MAXN*2];
bool backDiagUsed[MAXN*2];
bool colUsed[MAXN];

bool init(){
    cin >> n;
    if(!n) return false;

    nSol = 0;

    for(int i = 0; i < n; i++){
        cin >> gridStr[i];
        for(int j = 0; j < n; j++){
            canUse[i][j] = gridStr[i][j] == '.';
        }
    }

    return true;
}

int getDiag(int r, int c){
    return r + c;
}

int getBackDiag(int r, int c){
    return r + n - c;
}

void remQueen(int r, int c){
    diagUsed[getDiag(r, c)] = false;
    backDiagUsed[getBackDiag(r, c)] = false;
    colUsed[c] = false;
}

bool addQueen(int r, int c){
    if(diagUsed[getDiag(r, c)] || backDiagUsed[getBackDiag(r, c)] || colUsed[c] || !canUse[r][c]) return false;

    diagUsed[getDiag(r, c)] = true;
    backDiagUsed[getBackDiag(r, c)] = true;
    colUsed[c] = true;

    return true;
}

void solve(int r){
    if(r == n){
        nSol++;
        return ;
    }

    for(int c = 0; c < n; c++){
        if(addQueen(r, c)){
            solve(r + 1);
            remQueen(r, c);
        }
    }
}

int solve(){
    solve(0);
    return nSol;
}

int main(){
    for(int t = 1; init(); t++){
        cout<<"Case "<<t<<": "<<solve()<<"\n";
    }
}
