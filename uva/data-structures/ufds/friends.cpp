#include <bits/stdc++.h>
#define MAXN 30005
#define MAXM 500005

using namespace std;

int n, m;

int padre[MAXN];
int set_rank[MAXN];
int group_size[MAXN];

int get_padre(int i){
    if(i == padre[i]) return i;
    return padre[i] = get_padre(padre[i]);
}
void join_set(int i, int j){
    int padre_i = get_padre(i), padre_j = get_padre(j);
    if(padre_i != padre_j){
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
void init_disjoint_set(){
    for(int i = 0; i < n; i++)
        padre[i] = i, set_rank[i] = 0;
}

void init(){
    cin >> n >> m;

    fill(group_size, group_size + n, 0);

    init_disjoint_set();

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        join_set(a, b);
    }
}

int solve(){
    for(int i = 0; i < n; i++)
        group_size[get_padre(i)]++;

    return *max_element(group_size, group_size + n);
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    int T;
    cin >> T;

    while(T--){
        init();
        fprintf(out, "%d\n", solve());
    }
}
