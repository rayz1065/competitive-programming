#include <bits/stdc++.h>
#define MAXN 200005
#define MAXM 200005

using namespace std;

int n, m;

int padre[MAXN];
int set_rank[MAXN];
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

bool init(){
    cin >> n >> m;
    if(n == 0 && m == 0)
        return false;

    init_disjoint_set();

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        join_set(a, b);
    }

    return true;
}

int solve(){
    int s = 0;

    for(int i = 0; i < n; i++)
        if(get_padre(i) == i) s++;

    return s;
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    int t = 0;
    while(init()){
        fprintf(out, "Case %d: %d\n", ++t, solve());
    }
}
