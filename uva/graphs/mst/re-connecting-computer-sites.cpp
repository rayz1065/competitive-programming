#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int N;

set<pair<int, pair<int,int>>> archi;
int padre[MAXN];
int dim[MAXN];

int initialW;

int getPadre(int i){
    if(i == padre[i])
        return i;
    return padre[i] = getPadre(padre[i]);
}

void unionByRank(int a, int b){
    a = getPadre(a), b = getPadre(b);
    if(dim[a] > dim[b])
        padre[b] = a;
    else if(dim[a] < dim[b])
        padre[a] = b;
    else
        padre[a] = b, dim[b]++;
}

bool init(){
    if(!(cin >> N))
        return false;
    archi.clear();
    for(int i = 1; i < N + 1; i++)
        padre[i] = i, dim[i] = 1;

    initialW = 0;

    for(int i = 0; i < N - 1; i++){
        int a, b, w;
        cin >> a >> b >> w;
        initialW+= w;
        archi.insert({w, {a, b}});
    }

    int K;
    cin >> K;

    for(int i = 0; i < K; i++){
        int a, b, w;
        cin >> a >> b >> w;
        archi.insert({w, {a, b}});
    }

    int M;
    cin >> M;

    for(int i = 0; i < M; i++){
        int a, b, w;
        cin >> a >> b >> w;
    }
    return true;
}

int solve(){
    int isole = N, S = 0;
    for(auto i:archi){
        if(getPadre(i.second.first) != getPadre(i.second.second))
            isole--, unionByRank(i.second.first, i.second.second), S+= i.first;
        if(isole == 1)
            return S;
    }
    return -1;
}

int main(){
    FILE *out = stdout;
    bool fc = true;

    while(init()){
        if(fc)
            fc = false;
        else
            fprintf(out, "\n");

        fprintf(out, "%d\n%d\n", initialW, solve());
    }
}
