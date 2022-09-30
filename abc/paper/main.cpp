#include <bits/stdc++.h>
#define MAXN 75005
using namespace std;

vector<int> grafo[MAXN];
vector<int> grafoReverse[MAXN];
stack<int> ordine;
int componente[MAXN];
bool visited[MAXN];

void primaVisita(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            primaVisita(i);
    ordine.push(nodo);
}

int secondaVisita(int nodo, int comp){
    int S = 0;
    visited[nodo] = true;
    componente[nodo] = comp;
    for(auto i:grafoReverse[nodo])
        if(!visited[i])
            S+= secondaVisita(i, comp);
    return S + 1;
}

void verifica(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            verifica(i);
}

int paper(int N, int M, int A[], int B[]) {
    for(int i = 0; i < M; i++){
        grafo[A[i] - 1].push_back(B[i] - 1);
        grafoReverse[B[i] - 1].push_back(A[i] - 1);
    }

    for(int i = 0; i < N; i++){
        if(!visited[i])
            primaVisita(i);
    }

    fill(visited, visited + N, false);

    int maybe = ordine.top();

    verifica(maybe);
    for(int i = 0; i < N; i++){
        if(!visited[i])
            return 0;
    }
    
    fill(visited, visited + N, false);
    return secondaVisita(maybe, 1);
}
