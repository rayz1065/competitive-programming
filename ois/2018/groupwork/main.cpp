#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

int N, M;
vector<int> grafo[MAXN];
vector<int> appartenenza[MAXN];
bool connesso[MAXN][MAXN];
bool used[MAXN];

vector<pair<int, vector<int> > > listaGruppi;
vector<int> scelteMigliori;
/*void solve(int i, vector<int> scelte){
    if(i == listaGruppi.size()){
        if(scelte.size() > scelteMigliori.size())
            scelteMigliori = scelte;
        return;
    }
    if(!used[listaGruppi[i].a] && !used[listaGruppi[i].b] && !used[listaGruppi[i].c]){
        used[listaGruppi[i].a] = used[listaGruppi[i].b] = used[listaGruppi[i].c] = true;
        scelte.push_back(i);
        solve(i + 1, scelte);
        used[listaGruppi[i].a] = used[listaGruppi[i].b] = used[listaGruppi[i].c] = false;
        scelte.pop_back();
    }
    int rim = 0;
    for(int j = i + 1; j < listaGruppi.size(); j++){
        if(!used[listaGruppi[j].a] && !used[listaGruppi[j].b] && !used[listaGruppi[j].c])
            rim++;
    }
    if(scelte.size() + rim > scelteMigliori.size())
        solve(i + 1, scelte);
}*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>M;

    for(int i = 0; i < M; i++){
        int a, b;
        cin>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
        connesso[a][b] = true;
        connesso[b][a] = true;
    }

    for(int i = 0; i < N; i++){
        for(auto j:grafo[i]){
            if(j > i){
                for(auto p:grafo[j]){
                    if(p > j && connesso[p][i]){
                        listaGruppi.push_back({0, {i, j, p}});

                        int s = listaGruppi.size() - 1;
                        appartenenza[i].push_back(s);
                        appartenenza[p].push_back(s);
                        appartenenza[j].push_back(s);
                    }
                }
            }
        }
    }
    for(auto i:listaGruppi){
        set<int> com;
        for(auto j:i.second)
            for(auto a:appartenenza[j])
                com.insert(a);
        i.first = com.size() - 1;
    }
    sort(listaGruppi.begin(), listaGruppi.end());

    for(auto i:listaGruppi){
        bool cantUse = false;
        for(auto j:i.second){
            if(used[j])
                cantUse = true;
        }
        if(!cantUse){
            for(auto j:i.second){
                used[j] = true;
                for(auto a:appartenenza[j]){ // tutti i gruppi a cui appartengono i nodi del gruppo
                    for(auto n:listaGruppi[a]){ // tutti i nodi di appartenenza a questi gruppi
                        listaGruppi[a].first--; // togliamo un gruppo in comune
                    }
                }
            }
        }
    }
    cout<<scelteMigliori.size()<<endl;
}
