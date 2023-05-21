#include <bits/stdc++.h>
#define MAXN 30
using namespace std;

int N;

int adjMat[MAXN][MAXN];
int padre[MAXN];
set<pair<int, pair<int, int>>> archi;
vector<pair<int, pair<int, int>>> scelti;

int getPadre(int i){
    if(i == padre[i])
        return i;
    return getPadre(padre[i]);
}

void unisci(int a, int b){
    padre[getPadre(a)] = getPadre(b);
}

void init(){
    cin >> N;
    for(int i = 0; i < N; i++)
        padre[i] = i;

    archi.clear();
    scelti.clear();
    for(int i = 0; i < N; i++){
        int w;
        for(int j = 0; j < N; j++){
            scanf("%d, ", &adjMat[i][j]);
            if(i < j && adjMat[i][j] > 0)
                archi.insert({adjMat[i][j], {i, j}});
        }
    }
}

void solve(){
    int isole = N;
    for(auto i:archi){
        if(getPadre(i.second.first) != getPadre(i.second.second)){
            unisci(i.second.first, i.second.second);
            scelti.push_back(i);
            isole--;
        }
        if(isole == 1)
            return ;
    }
}

int main(){
    FILE *out = stdout;
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        solve();

        fprintf(out, "Case %d:\n", t);

        for(auto i:scelti){
            fprintf(out, "%c-%c %d\n", i.second.first + 'A', i.second.second + 'A', i.first);
        }
    }
}
