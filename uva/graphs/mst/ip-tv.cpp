#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int N, M;

set<pair<int, pair<int,int>>> archi;
map<string, int> numCity;
int padre[MAXN];
int dim[MAXN];

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

void init(){
    archi.clear();
    numCity.clear();

    cin >> N >> M;
    for(int i = 0; i < N; i++)
        padre[i] = i, dim[i] = 1;

    int currLast = 0;

    for(int i = 0; i < M; i++){
        string a, b;
        int w;
        cin >> a >> b >> w;
        int numA, numB;
        if(numCity.count(a) == 0)
            numCity[a] = currLast++;
        if(numCity.count(b) == 0)
            numCity[b] = currLast++;
        numA = numCity[a], numB = numCity[b];

        archi.insert({w, {numA, numB}});
    }
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
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        if(t > 1)
            fprintf(out, "\n");
        init();
        fprintf(out, "%d\n", solve());
    }
}
