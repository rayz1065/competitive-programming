#include <bits/stdc++.h>
#define MAXN 400005

using namespace std;
long long N, Q;
long long valori[MAXN];
long long fenwick[MAXN];
long long entrata[MAXN], uscita[MAXN], tempo = 1;
vector<long long> albero[MAXN];

long long sum(long long i){
    long long S = 0;
    while(i > 0)
        S+= fenwick[i], i-= ((i) & (-i));
    return S;
}

void add(long long i, long long val){
    while(i < MAXN)
        fenwick[i]+= val, i+= ((i) & (-i));
}


void dfs(long long nodo, long long padre){
    entrata[nodo] = tempo++;
    add(entrata[nodo], valori[nodo]);

    for(auto i:albero[nodo])
        if(i != padre)
            dfs(i, nodo);

    uscita[nodo] = tempo++;
}

long long calcolaSottoalbero(long long nodo){
    return sum(uscita[nodo]) - sum(entrata[nodo] - 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>Q;
    for(long long i = 1; i <= N; i++){
        cin>>valori[i];
    }
    for(long long i = 0; i < N - 1; i++){
        long long a, b;
        cin>>a>>b;
        albero[a].push_back(b);
        albero[b].push_back(a);
    }

    dfs(1, 0);

    for(long long i = 0; i < Q; i++){
        long long op, nodo;
        cin >> op >> nodo;
        if(op == 2){
            cout<<calcolaSottoalbero(nodo)<<endl;
        }
        else{
            long long val;
            cin>>val;
            add(entrata[nodo], val - valori[nodo]);
            valori[nodo] = val;
        }
    }
}
