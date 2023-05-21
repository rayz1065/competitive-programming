#include <bits/stdc++.h>
#define MAXIN 10000
#define ALF 30

using namespace std;

char input[MAXIN];
bool percorso[ALF][ALF];

void init(){
    cin >> input;
    memset(percorso, false, sizeof(percorso));
}

int contaRami(int nodo){
    int S = 0;
    for(int i = 0; i < ALF; i++)
        S+= percorso[nodo][i];
    return S;
}

void solve(int &i, char nodo){
    i++;
    while(i < MAXIN && input[i] != nodo){
        percorso[nodo - 'A'][input[i] - 'A'] = percorso[input[i] - 'A'][nodo - 'A'] = true;
        solve(i, input[i]);
    }
    i++;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();

        int i = 0;
        solve(i, input[0]);

        fprintf(out, "Case %d\n", t);
        for(int i = 0; i < ALF; i++){
            int r = contaRami(i);
            if(r > 0)
                fprintf(out, "%c = %d\n", i + 'A', contaRami(i));
        }
    }
}
