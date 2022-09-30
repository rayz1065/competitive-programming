#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int N;
vector<int> grafo[MAXN];
int monete[MAXN];
int spost[MAXN];
int costo[MAXN];

int dfs(int nodo){
    for(auto i:grafo[nodo]){
        dfs(i);
        costo[nodo]+= costo[i] + abs(spost[i]);
        spost[nodo]+= spost[i];
    }
    spost[nodo]+= monete[nodo] - 1;
    return costo[nodo];
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>N;
    for(int i = 1; i <= N; i++)
        in >> monete[i];

    for(int i = 2; i <= N; i++){
        int p;
        in >> p;
        grafo[p].push_back(i);
    }

    out<<dfs(1)<<endl;
}
