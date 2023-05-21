#include <bits/stdc++.h>
#define MAXN 30005
#define MAXM 505

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
        int k;
        cin >> k;

        assert(k > 0);

        int p;
        cin >> p;

        for(int j = 1; j < k; j++){
            int a;
            cin >> a;
            join_set(a, p);
        }
    }

    return true;
}

int solve(){
    int s = 0;

    for(int i = 0; i < n; i++)
        if(in_same_set(0, i))
            s++;

    return s;
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    while(init()){
        fprintf(out, "%d\n", solve());
    }
}
