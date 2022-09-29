#include <bits/stdc++.h>
#define MAXN 5000
using namespace std;

fstream in, out;
vector<int> metaData[MAXN];
vector<int> grafo[MAXN];
int N = 0;

void prendiInput(int nodo, int padre){
    if(padre != -1)
        grafo[padre].push_back(nodo);
    int numeroDiFigli, numeroMetaData;
    in >> numeroDiFigli >> numeroMetaData;

    for(int i = 0; i < numeroDiFigli; i++){
        prendiInput(N++, nodo);
    }
    for(int i = 0; i < numeroMetaData; i++){
        int d;
        in >> d;
        metaData[nodo].push_back(d);
    }
}

int memo[MAXN];
bool solved[MAXN];

int getValue(int nodo){
    if(solved[nodo])
        return memo[nodo];

    solved[nodo] = true;
    if(grafo[nodo].size() == 0){
        int sommaMeta = 0;
        for(auto j:metaData[nodo])
            sommaMeta+= j;
        return memo[nodo] = sommaMeta;
    }
    int S = 0;
    for(auto j:metaData[nodo]){
        if(j > 0 && j <= grafo[nodo].size()){
            S+= getValue(grafo[nodo][j - 1]);
        }
    }
    return memo[nodo] = S;
}

int main(){
    in.open("input8.txt");

    prendiInput(N++, -1);

    int sommaMetaData = 0;
    for(int i = 0; i < N; i++){
        for(auto j:metaData[i])
            sommaMetaData+= j;
    }

    cout<<sommaMetaData<<endl;
    cout<<getValue(0)<<endl;
}
