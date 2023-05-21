#include <bits/stdc++.h>

using namespace std;

int N, M;

set<pair<int, pair<int, int>>> archi;

vector<int> padre;

bool init(){
    archi.clear();
    padre.clear();

    cin >> N >> M;
    if(N == 0 && M == 0)
        return false;

    padre.resize(N);
    for(int i = 0; i < N; i++)
        padre[i] = i;

    for(int i = 0; i < M; i++){
        int a, b, w;
        cin >> a >> b >> w;
        archi.insert({w, {a, b}});
    }

    return true;
}

int getPadre(int i){
    if(i == padre[i])
        return i;
    return padre[i] = getPadre(padre[i]);
}

void unisci(int a, int b){
    padre[getPadre(a)] = getPadre(b);
}

int solve(){
    if(N == 1)
        return 0;
    int S = 0, isole = N;

    for(auto i:archi){
        if(getPadre(i.second.first) != getPadre(i.second.second))
            S = i.first, isole--, unisci(i.second.first, i.second.second);
        if(isole == 1)
            return S;
    }
    return -1;
}

int main(){
    while(init()){
        int S = solve();
        if(S == -1)
            cout<<"IMPOSSIBLE\n";
        else
            cout<<S<<"\n";
    }
}
