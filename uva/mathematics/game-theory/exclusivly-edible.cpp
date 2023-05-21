#include <bits/stdc++.h>
#define MAXN 50
#define DEBUGMODE 0
using namespace std;
int aSC, bSC;
int memo[MAXN][MAXN][MAXN][MAXN];
bool willWin(int a, int b, int A, int B){
    if(a == aSC && b == bSC && A == aSC + 1 && B == bSC + 1){
        if(DEBUGMODE){
            cout<<a<<" "<<b<<" "<<A<<" "<<B<<endl;
            for(int i = a; i < A; i++){
                for(int j = b; j < B; j++)
                    cout<<((i == aSC && j == bSC)?"X":"O")<<" ";
                cout<<endl;
            }
            cout<<"rip\n\n";
        }
        return false;
    }
    if(memo[a][b][A][B] == -1){ // non c'è ancora alcun valore
        memo[a][b][A][B] = false;
        for(int i = a + 1; i <= aSC && memo[a][b][A][B] == false; i++)
            if(!willWin(i, b, A, B))
                memo[a][b][A][B] = true;
        for(int i = A - 1; i > aSC && memo[a][b][A][B] == false; i--)
            if(!willWin(a, b, i, B))
                memo[a][b][A][B] = true;
        for(int i = b + 1; i <= bSC && memo[a][b][A][B] == false; i++)
            if(!willWin(a, i, A, B))
                memo[a][b][A][B] = true;
        for(int i = B - 1; i > bSC && memo[a][b][A][B] == false; i--)
            if(!willWin(a, b, A, i))
                memo[a][b][A][B] = true;
    }
    if(DEBUGMODE){
        cout<<a<<" "<<b<<" "<<A<<" "<<B<<endl;
        for(int i = a; i < A; i++){
            for(int j = b; j < B; j++)
                cout<<((i == aSC && j == bSC)?"X":"O")<<" ";
            cout<<endl;
        }
        cout<<((memo[a][b][A][B])?"win":"rip")<<"\n\n";
    }
    return memo[a][b][A][B];
}

int main(){
    int T;
    cin>>T;
    for(int c=0; c<T; c++){
        int N, M;
        cin>>N>>M>>aSC>>bSC;
        for(int i=0; i<MAXN; i++)
            for(int j=0; j<MAXN; j++)
                for(int h=0; h<MAXN; h++)
                    for(int k=0; k<MAXN; k++)
                        memo[i][j][h][k]=-1;
        cout<<((willWin(0, 0, N, M))?"Gretel":"Hansel")<<endl;
    }
}
