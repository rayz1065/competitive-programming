#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

pair<int, int> bst[MAXN];
int padre[MAXN];
int valori[MAXN];
int N;

void computeTree(int nodo, int i){
    if(valori[i] < valori[nodo]){
        if(bst[nodo].first == -1)
            bst[nodo].first = i;
        else
            computeTree(bst[nodo].first, i);
    }
    else{
        if(bst[nodo].second == -1)
            bst[nodo].second = i;
        else
            computeTree(bst[nodo].second, i);
    }
}

void postOrder(int nodo, FILE *out){
    if(bst[nodo].first != -1)
        postOrder(bst[nodo].first, out);
    if(bst[nodo].second != -1)
        postOrder(bst[nodo].second, out);
    fprintf(out, "%d\n", valori[nodo]);
}

int main(){
    int v;
    N = 0;
    while(cin >> v)
        valori[N] = v, bst[N] = {-1, -1}, N++;

    for(int i = 1; i < N; i++){
        computeTree(0, i);
    }

    postOrder(0, stdout);
}
