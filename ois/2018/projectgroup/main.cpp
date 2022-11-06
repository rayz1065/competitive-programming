#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

chrono::_V2::system_clock::time_point start_time;

int timeout_acc;
bool is_timeout () {
#ifdef DEBUG
    return false;
#endif
    if ((++timeout_acc % 10000) != 0) {
        return false;
    }
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    long long milliseconds = chrono::duration_cast<std::chrono::milliseconds>(
            elapsed).count();
    return milliseconds > 1950;
}

int N, M;
vector<int> grafo[MAXN];
bool connesso[MAXN][MAXN];
bool used[MAXN];
int overlaps[MAXN];

struct gruppo{
    int a;
    int b;
    int c;
};
vector<gruppo> listaGruppi;
vector<int> scelteMigliori;

void print_best_solution () {
    cout<<scelteMigliori.size()<<endl;
    for(auto i:scelteMigliori)
        cout<<listaGruppi[i].a<<" "<<listaGruppi[i].b<<" "<<listaGruppi[i].c<<endl;
}

void solve(int i, vector<int> &scelte){
    if (is_timeout()) {
        print_best_solution();
        exit(0);
    }
    if(i == listaGruppi.size()){
        if(scelte.size() > scelteMigliori.size())
            scelteMigliori = scelte;
        return;
    }
    if(!used[listaGruppi[i].a] && !used[listaGruppi[i].b] && !used[listaGruppi[i].c]){
        used[listaGruppi[i].a] = used[listaGruppi[i].b] = used[listaGruppi[i].c] = true;
        scelte.push_back(i);
        solve(i + 1, scelte);
        scelte.pop_back();
        used[listaGruppi[i].a] = used[listaGruppi[i].b] = used[listaGruppi[i].c] = false;
    }
    int rim = 0;
    for(int j = i + 1; j < listaGruppi.size(); j++){
        if(!used[listaGruppi[j].a] && !used[listaGruppi[j].b] && !used[listaGruppi[j].c])
            rim++;
    }
    if(scelte.size() + rim > scelteMigliori.size())
        solve(i + 1, scelte);
}

bool cmp_groups (const gruppo &a, const gruppo &b) {
    return overlaps[a.a] + overlaps[a.b] + overlaps[a.c] < \
           overlaps[b.a] + overlaps[b.b] + overlaps[b.c];
}

int main(){
    start_time = chrono::high_resolution_clock::now();
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
                        listaGruppi.push_back({i, j, p});
                        overlaps[i]++, overlaps[j]++, overlaps[p]++;
                    }
                }
            }
        }
    }
    sort(listaGruppi.begin(), listaGruppi.end(), cmp_groups);
    vector<int> scelte;
    solve(0, scelte);
    print_best_solution();
}
