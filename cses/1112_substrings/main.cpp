#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int N;
int Lc;
char A[MAXN];
int T[MAXN];

int lastRiga = 0;

set<string> presenti;

void stampa(string S, int l, bool right){
    if(l == Lc){
        if(presenti.find(S) != presenti.end()){
            cout<<S<<"\t";
            if(++lastRiga == 6){
                lastRiga = 0;
                cout<<endl;
            }
        }
        else{
            presenti.insert(S);
        }
        return;
    }
    if(right){
        for(int i = 0; i < 26; i++)
            stampa(S + (char)(65 + i), l + 1, 1);
    }
    else
        for(int i = 0; i < 26; i++){
            stampa((char)(65 + i) + S, l + 1, 0);
            if(l + 1 < Lc)
                stampa((char)(65 + i) + S, l + 1, 1);
        }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>Lc;
    cin>>A;
    N = strlen(A);

    for(int i = 1, j = 0; i < N;){
        if(A[i] == A[j])
            T[i++] = ++j;
        else{
            while(j > 0 && T[i] == 0){
                j = T[j - 1];
            }
            i++;
        }
    }

    for(int i = 0; i < N; i++)
        cout<<A[i]<<"\t";
    cout<<endl;
    for(int i = 0; i < N; i++)
        cout<<T[i]<<"\t";
    cout<<endl;
    stampa(A, N, 0);
    stampa(A, N, 1);
}
