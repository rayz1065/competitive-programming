#include <bits/stdc++.h>
#define MAXN 200
using namespace std;

int N;
bool daa[MAXN][MAXN];
bool reachable[MAXN];
bool visited[MAXN];
char linea[MAXN*2 + 5];
int currentDominator = -1;

void fillReachable(int nodo){
    reachable[nodo] = true;
    for(int i = 0; i < N; i++)
        if(daa[nodo][i] && !reachable[i])
            fillReachable(i);
}

void init(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cin >> daa[i][j];
    }
    fill(reachable, reachable + N, false);
    fill(visited, visited + N, false);
    currentDominator = -1;
    fillReachable(0);

    linea[0] = linea[2*N] = '+';
    linea[2*N + 1] = '\0';
    for(int i = 1; i < 2*N; i++)
        linea[i] = '-';
}

void dfsAndAvoid(int nodo, int avoid){
    visited[nodo] = true;
    for(int i = 0; i < N; i++){
        if(daa[nodo][i] && i != avoid && !visited[i])
            dfsAndAvoid(i, avoid);
    }
}

void setCurrentDominator(int source, int x){
    if(x == currentDominator)
        return ;
    currentDominator = x;
    fill(visited, visited + N, false);
    if(x != source)
        dfsAndAvoid(source, x);
}

bool isXDominatorOfY(int source, int x, int y){
    if(!reachable[y])
        return false;
    setCurrentDominator(source, x);
    return !(visited[y]);
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "Case %d:\n", t);
        for(int i = 0; i < N; i++){
            fprintf(out, "%s\n|", linea);
            for(int j = 0; j < N; j++){
                fprintf(out, "%c|", ((isXDominatorOfY(0, i, j))?'Y':'N'));
            }
            fprintf(out, "\n");
        }
        fprintf(out, "%s\n", linea);
    }
    return 0;
}
