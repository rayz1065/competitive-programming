#include <bits/stdc++.h>
#define MAXN 10000005
#define getchar getchar
using namespace std;

int N, M;
char andata[MAXN], ritorno[MAXN], pattern[MAXN];
int T[MAXN];

inline char getNextChar(){
    char c = getchar();
    while(c != 118 && c != 94 && c != 60 && c != 62)
        c = getchar();
    return c;
}

int risolvi(char pagliaio[]){
    int i = 0, j = 0; // i è l'indice del pagliaio, j è l'indice della pattern
    int S = 0; // soluzione

    while(i < N){
        if(pagliaio[i] == pattern[j]){
            i++, j++;
            if(j == M)
                j = T[j - 1], S++;
        }
        else{
            if(j == 0)
                i++;
            else
                j = T[j - 1];
        }
    }
    return S;
}

int main(){
    cin.tie(NULL);
    cin>>N;
    for(int i = 0; i < N; i++){
        char d = getNextChar();
        andata[i] = ((d == '^')?'<':'>');
    }
    for(int i = N - 1; i >= 0; i--){
        char d = getNextChar();
        ritorno[i] = ((d == 'v')?'<':'>');
    }

    cin>>M;
    for(int i = 0; i < M; i++)
        cin>>pattern[i];

    int i = 1, j = 0;
    // T[0] = 0 di base
    while(i < M){
        if(pattern[i] == pattern[j])
            T[i++] = ++j;
        else{
            while(j > 0 && T[i] == 0){
                j = T[j - 1];
                if(pattern[i] == pattern[j])
                    T[i] = j + 1;
            }
            i++;
        }
    }
    int S = 0;
    S+= risolvi(andata);
    S+= risolvi(ritorno);
    cout<<S;
}
