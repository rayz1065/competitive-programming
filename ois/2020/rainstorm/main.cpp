#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
#define MAXR 100005

using namespace std;

int n, m;

vector<pair<int, int>> to_add[MAXR];
int padre[MAXN];

int get_padre(int i){
    if(i == padre[i]) return i;
    return padre[i] = get_padre(padre[i]);
}

void merge_set(int i, int j){
    padre[get_padre(i)] = get_padre(j);
}

int solve(){
    int isole = n, curr_weight = MAXR - 1;

    while(curr_weight > 0){
        for(auto &i:to_add[curr_weight])
            if(get_padre(i.first) != get_padre(i.second))
                merge_set(i.first, i.second), isole--;

        if(isole == 1)
            return curr_weight;
        curr_weight--;
    }
    // ??
    return -1;
}

int main(){
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b, r;
        cin >> a >> b >> r;

        to_add[r].push_back({a, b});
    }

    for(int i = 0; i < n; i++)
        padre[i] = i;

    cout<<solve()<<"\n";
}
