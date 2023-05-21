#include <bits/stdc++.h>
#define MAXN 200005
#define MAXM 100005

using namespace std;

int n, m;
int owed[MAXN];
pair<int, int> fr[MAXM];

map<string, int> id_persona;
//string nome_persona[MAXN];

int get_id(string p){
    if(id_persona.count(p) == 1)
        return id_persona[p];

    //nome_persona[n] = p;
    return id_persona[p] = n++;
}

int padre[MAXN];
int set_rank[MAXN];
int set_size[MAXN];

int get_padre(int i){
    if(i == padre[i]) return i;
    return padre[i] = get_padre(padre[i]);
}
void join_set(int i, int j){
    int padre_i = get_padre(i), padre_j = get_padre(j);
    if(padre_i != padre_j){
        set_size[padre_i] = set_size[padre_j] + set_size[padre_i];
        set_size[padre_j] = set_size[padre_i];

        if(set_rank[padre_i] > set_rank[padre_j]){
            padre[padre_j] = padre_i;
        }
        else if(set_rank[padre_j] > set_rank[padre_i]){
            padre[padre_i] = padre_j;
        }
        else{
            padre[padre_i] = padre_j;
            set_rank[padre_j]++;
        }
    }
}
bool in_same_set(int i, int j){
    return get_padre(i) == get_padre(j);
}

void init(){
    n = 0;
    cin >> m;

    id_persona.clear();

    for(int i = 0; i < m; i++){
        string a, b;
        cin >> a >> b;
        fr[i] = {get_id(a), get_id(b)};
    }

    for(int i = 0; i < n; i++)
        padre[i] = i, set_size[i] = 1, set_rank[i] = 0;
}

void solve(FILE *out){
    for(int i = 0; i < m; i++){
        join_set(fr[i].first, fr[i].second);
        fprintf(out, "%d\n", set_size[get_padre(fr[i].first)]);
    }
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    int N;
    cin >> N;

    while(N--){
        init();
        solve(out);
    }
}
