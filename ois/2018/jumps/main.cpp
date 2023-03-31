#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int N;
string parole[MAXN];
map<string, int> idParola;
bool grafo[MAXN][MAXN];

bool solved[MAXN];
int depth[MAXN];

int dfs(int nodo){
    if(solved[nodo])
        return depth[nodo];
    solved[nodo] = true;

    int S = 0;
    for(int i = 0; i < N; i++){
        if(grafo[nodo][i]){
            S = max(S, dfs(i) + 1);
        }
    }
    return depth[nodo] = S;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N;
    for(int i = 0; i < N; i++){
        in >> parole[i];
        idParola[parole[i]] = i;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < parole[i].length(); j++){ /// tutte le parole con un carattere in meno
            string memo = parole[i];
            memo.erase(memo.begin() + j, memo.begin() + j + 1);
            if(idParola.count(memo) == 1)
                grafo[i][idParola[memo]] = true;
        }
        for(int j = 0; j < parole[i].length(); j++){ /// sostituiamo il carattere j con uno che si trova dopo nella stringa e alfabeto
            for(int k = j + 1; k < parole[i].length(); k++){
                if(parole[i][k] > parole[i][j]){
                    string memo = parole[i];
                    memo[j] = parole[i][k];

                    if(idParola.count(memo) == 1)
                        grafo[i][idParola[memo]] = true;
                }
            }
        }
    }

    int S = 0;
    for(int i = 0; i < N; i++){
        S = max(S, dfs(i) + 1);
    }
    cout<<S<<endl;
}
