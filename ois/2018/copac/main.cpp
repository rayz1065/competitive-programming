#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int N, M;
vector<int> grafo[MAXN];
vector<int> soluzioni;
bool used[MAXN];

int dfs(int padre){
    used[padre] = true;
    int figliTot = 0;
    bool valid = true;

    for(auto figlio:grafo[padre]){
        if(!used[figlio]){
            int sottoG = dfs(figlio);
            if(sottoG>N/2)
                valid = false;
            figliTot+= sottoG;
        }
    }
    if(figliTot+1<N/2)
        valid = false;

    if(valid)
        soluzioni.push_back(padre);

    return figliTot+1;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    in>>N;
    M=N-1;
    for(int i=0; i<M; i++){
        int a, b;
        in>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }

    dfs(1);
    sort(soluzioni.begin(), soluzioni.end());

    for(auto i:soluzioni)
        out<<i<<endl;
}
