#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

vector<int> grafo[MAXN];
stack<int> ordine;
bool visited[MAXN];

void visita(int nodo){
    visited[nodo] = true;
    for(int i:grafo[nodo])
        if(!visited[i])
            visita(i);
    ordine.push(nodo);
}

int main(){
    ios::sync_with_stdio(false);
    int N, M, P;
    cin>>N>>M>>P;
    for(int i = 0; i < M; i++){
        int da, a;
        cin>>da>>a;
        grafo[da].push_back(a);
    }

    for(int i = 0; i < N; i++)
        if(!visited[i])
            visita(i);

    double perc[N] = {};
    perc[0] = 1;
    int S = 0;
    double best = 0;
    while(!ordine.empty()){
        int nodo = ordine.top();
        int div = grafo[nodo].size();
        if(div == 0){
            if(perc[nodo] > best){
                best = perc[nodo];
                S = nodo;
            }
        }
        for(int i:grafo[nodo])
            perc[i]+= perc[nodo]/div;
        ordine.pop();
    }
    cout<<S;
}
